#include "type.h"
#include "protect.h"
#include "regctl.h"
#include "string.h"
#include "sys\proc.h"
#include "sys\kernel.h"
#include "fos\memory.h"
#include "fos\fs.h"
#include "fos\blk.h"

int init_mm()
{
    int i;
    
    Phy_mm8 = 0;
    Phy_mm32 = 0;
    Mm_size = Phy_mm32[Add2mm32(Hd_mm)];
    
    /*将2M以内的内存标记为不可用*/
    for(i = 0;i < Add2pg8(Page_mm);i ++)
        Mm_map[i] = Un_avl;
    /*2M以外的内存标记为可用*/ 
    for(i = Add2pg8(Page_mm);i < Add2pg8(Mm_size);i ++)
        Mm_map[i] = Im_avl;
    
    return 0;
}
int get_free_buff()
{
    int i;
    
    for(i = Add2pg8(Page_mm);i < Add2pg8(Buff_mm);i ++)
    {
        if(Mm_map[i] == Im_avl)
        {
             Mm_map[i] ++;        
             return i;
        }
    }  
    return 0;
}
int get_free_app()
{
    int i;

    for(i = Add2pg8(Buff_mm);i < Add2pg8(Mm_size);i ++)
    {
        if(Mm_map[i] == Im_avl)
        {
             Mm_map[i] ++;
             return i;
        }
    }
    return 0;
}
void free_page(unsigned long addr)
{
     if((addr < Buff_mm) || (addr >= Mm_size))
     {
           printk("trying to free nonexistent page!");
                 return;
     }
     addr = Add2pg8(addr);
     if(Mm_map[addr] --)   
          return;
     Mm_map[addr] = Im_avl;
     printk("trying to free free page!"); 
}
void free_page_tables(unsigned long base)
{
     int i,j;
     unsigned long *pg_dir;
     unsigned long *pg_table;

     if (base & 0xfff)
         printk("free_page_tables called with wrong alignment!");
     
     pg_dir = base;
     for(i = 0;i < 1024;i ++)
     {
           if(pg_dir[i] & PG_P)
           {
                pg_table = pg_dir[i] & 0xfffff000;
                for(j = 0;j < 1024;j ++)
                {
                      if((pg_table[j] & PG_P) && ((pg_table[j] & 0xfffff000) >= Buff_mm))
                           free_page(pg_table[j] & 0xfffff000);
                      pg_table[j] = 0;
                }
                free_page(pg_dir[i] & 0xfffff000);
           }
           pg_dir[i] = 0;
     }
}
void copy_page_tables(unsigned long from,unsigned long to)
{
     int i,j;
     unsigned long * from_dir, * to_dir;
     unsigned long * from_table, * to_table;
     unsigned long this_page,tmp;
     
     if ((from & 0xfff) || (to & 0xfff))
           printk("copy_page_tables called with wrong alignment\n");
     
     from_dir = from;
     to_dir   = to;
     
     for(i = 0;i < 1024;i ++)
     {     	     
           if(to_dir[i] & PG_P)
           {
                printk("copy_page_tables: already exist!\n");  
                continue;
           }
           if(!(from_dir[i] & PG_P))
           {
           	    to_dir[i] = 0;
                continue;
           }
           
           from_table = from_dir[i] & 0xfffff000;  
           tmp = pg2add8(get_free_app());
           to_table = tmp;
           to_dir[i] = tmp | 7;
                    
           for(j = 0;j < 1024;j ++)
           {           	     	    
                 if(from_table[j] & PG_P)
                 {
                         /*this_page = from_table[j] & (~2);*/    /*复位r/w位*/
                         /*to_table[j] = this_page; */  
                         /*1G以内的作为内核，除了内核堆栈以外，其余共享,1G以外的写时复制*/    
                         if(i >= 256)
                         {
                         	   this_page = from_table[j] & (~2);
                         	   Mm_map[Add2pg8(this_page)]++;
                         }
                         else
                         {
                         	    this_page = from_table[j];
                         }
                         from_table[j] = this_page;
                         to_table[j] = this_page;
                 }
                 else
                 	       to_table[j] = 0;
           }
     }
     cr3_reload();
}
/*先找到页目录项，然后再找页表项*/
unsigned long put_page(unsigned cr3,unsigned long page,unsigned long address)
{
     unsigned long *pg_dir,*pg_table;
     unsigned long nr,tmp;
     
     if((page < Buff_mm) || (page >= Mm_size))
     {
           printk("trying to put nonexistent page!");
                 return 0;
     }
     pg_dir = cr3 & 0xfffff000;
     nr = address >> 22;                                /*下标是从0算起的*/
     if(pg_dir[nr] & PG_P)
           pg_table = pg_dir[nr] & 0xfffff000;
     else
     {
           tmp = pg2add8(get_free_app());
           pg_table = tmp;
           pg_dir[nr] = tmp | 7;
     }
     pg_table[(address >> 12) & 0x3ff] = page | 7;
     
     return page;
}
void do_page(unsigned long cr2,unsigned long error_no)
{
    /*通过中断出错码判断出错类型*/
    if(error_no & 1)
        do_wp_page(cr2,error_no);
    else
        do_no_page(cr2,error_no);
}
void cr3_reload()
{
     put_cr3_long(get_cr3_long());
}
void un_wp_page(unsigned long * table_entry)
{
     unsigned long old_page,new_page;
     
     old_page = 0xfffff000 & *table_entry;
     if (Mm_map[Add2pg8(old_page)] == 1) 
     {
         *table_entry |= 2;
         cr3_reload();
         return;
     }
     Mm_map[Add2pg8(old_page)]--;
     new_page = pg2add8(get_free_app());
     *table_entry = new_page | 7;
     cr3_reload();
     copy_page(old_page,new_page);
}
void do_wp_page(unsigned long address,unsigned long error_no)
{
     unsigned long *pg_dir,*pg_table;
     unsigned long nr;
     
     pg_dir = get_cr3_long() & 0xfffff000;
     nr = address >> 22;                                /*下标是从0算起的*/
     pg_table = pg_dir[nr] & 0xfffff000;
     un_wp_page(&pg_table[(address >> 12) & 0x3ff]);    
}
int try_to_share(unsigned long address,struct Task_struct *p)
{
	  unsigned long v_addr;
	  unsigned long v_dir;
	  unsigned long v_page;
	  unsigned long *dir;
	  unsigned long *from_page,*to_page;
    
	  v_addr = p -> data_start + address;
	  v_dir = v_addr >> 22;
	  v_page = v_addr >> 12 & 0x3ff;
	  
    dir = p -> tss.cr3 & 0xFFFFF000;
    
    /*页目录不存在*/
    if(!(dir[v_dir] & 1))
        return 0;
    from_page = dir[v_dir] & 0xFFFFF000;
    /*如果不存在,或者脏位的话,则不能共享*/
    if((from_page[v_page] & 0x41) != 0x1)
    	  return 0;
    
    /*共享页面*/
    dir = current -> tss.cr3;
    if(!(dir[v_dir] & 1))
    	  dir[v_dir] = pg2add8(get_free_app()) | 7;
    to_page = dir[v_dir] & 0xFFFFF000;
    
    /*写保护*/
    from_page[v_page] = from_page[v_page] & ~2;
    to_page[v_page] = from_page[v_page];
    cr3_reload();
    
    Mm_map[to_page[v_page] >> 12] ++;
        
    return 1;	  
}
int share_page(unsigned long address)
{
	  int i;
	  
	  if(current -> file_fd = -1)
	  	   return 0;
	  if(files[current -> file_fd].counts < 2)
	  	   return 0;
	  
	  for(i = 1;i < NR_TASKS;i ++)
	  {
	  	   if(Tasks[i] && (current != Tasks[i]) && (current -> file_fd == Tasks[i] -> file_fd))
	  	   {
	  	   	    if(try_to_share(address,Tasks[i]))
	  	   	    	   return 1;
	  	   }
	  }
}
void do_no_page(unsigned long address,unsigned long error_no)
{
     unsigned long tmp;
     unsigned long page;
 
     address &= 0xfffff000;
     tmp = address - current->data_start;
     if(address >= current->data_end)
     {
     	    put_page(get_cr3_long(),pg2add8(get_free_app()),address);
     	    return;
     }
     /*首先判断内存中是否有所需要的数据，如果有，共享*/
     if (share_page(tmp))
         return;
     if (!(page = pg2add8(get_free_app())))
         return;
     
     /*如果所需要的数据不在内存中,则从软盘读取*/
     request_zone(READ, tmp);
}
