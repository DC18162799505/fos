#include "type.h"
#include "protect.h"
#include "regctl.h"
#include "string.h"
#include "sys\proc.h"
#include "sys\kernel.h"
#include "fos\memory.h"
#include "fos\fs.h"
#include "fos\blk.h"

void init_fs()
{
	   int i;
	   
	   for(i = 0;i < NR_FILES;i ++)
	   {
	   	    files[i].fd = i;
	   	    files[i].counts = 0;
	   }
	   super_block.dirt = 0;
	   super_block.lock = 0;
	   super_block.read = 0;
	   super_block.waiting = NULL;	    
}

void init_Zone(struct Zone* tmp)
{
	   tmp -> lock = 0;
	   tmp -> dirt = 0;
	   tmp -> uptodata = 0;
	   tmp -> waiting = NULL;
}
int request_fs()
{
	   int i,j;
	   
	   for(i = 0;i < NR_FILES;i ++)
	   {
	   	   if(!files[i].counts)
	   	   {
	   	   	   files[i].counts = 1;
	   	   	   for(j = 0;j < 8;j ++)
	   	   	   	   init_Zone(&files[i].zones[j]);  
	   	   }
	   	   return i;
	   }
}

/*计算fat表*/
int cal_clus(int head)
{
	  int odev,clus;
	  int v1,v2,v3;
	  
	  odev = head & 1;
	  head = head >> 1;
	  head = head * 3;
	  
	  v1 = (int)super_block.Fat_sec[head] & 0x0FF;
	  v2 = (int)super_block.Fat_sec[head + 1] & 0x0FF;
	  v3 = (int)super_block.Fat_sec[head + 2] & 0x0FF;
	  
	  if(odev)
	  {
	  /*奇数*/
	      clus = (v2 >> 4) | (v3 << 4);
	  }
	  else
	  {
	  /*偶数*/
	      clus = v1 | ((v2 & 0x0F) << 8);
	  } 
	  
	  return clus;
}
void request_zone(int rw,unsigned long addr)
{
	   int head,sectors,block;
	   
	   /*计算要读取的开始扇区*/
	   head = files[current -> file_fd].fat.fstclus;
	   sectors = (addr + 511) / 512;
	   
	   while(sectors --)
	        head = cal_clus(head);
	   block = addr / Page_size;
	   files[current -> file_fd].zones[block].sector = head + FL_DATA - 2;
	   operation_block(rw, &(files[current -> file_fd].zones[block]));
}
int load_file(char *fname)
{
	   int i,j,p,fd,bool_c;
	   char *pr;
	   /*char  v1[2],v2[2];*/
	   unsigned char *buf;
	   
	   fd = request_fs();
	   current -> file_fd = fd;
	   
	   /*寻找fname文件*/
	   for(i = 0;i < 224;i ++)
	   {
	   	   p = i * 32;
	   	   pr = &super_block.Root_dir[p];
	   	   bool_c = 0;
	   	   for(j = 0;j < 8;j ++,pr ++)
	   	   {
	   	       if(*pr == ' ' || (fname[j] == '.'))
	   	       {
	   	       	   if(*pr == ' ' && (fname[j] == '.'))
	   	       	        break;
	   	       }
	   	       if(*pr == fname[j])
	   	       	     continue;
	   	       bool_c = 1;
	   	       break;
	   	   }
	   	   if(bool_c)
	   	   	   continue;
	   	   else
	   	   	   break;
	   }
	   if(i == 224)
	   	    return 0;
	   i = 0;
	   while(fname[i] != '.')
	   {
	      files[fd].fat.name[i] = fname[i];
	      i ++;
	   }
	   files[fd].fat.name[i] = '\0';
	   for(j = 0;j < 3;j ++)
	      files[fd].fat.name_ext[j] = fname[++ i];
	   files[fd].fat.fstclus = 0;
	   files[fd].fat.fstclus = (int16)super_block.Root_dir[p + 26];
	   files[fd].fat.size = (int32)super_block.Root_dir[p + 28];
	   files[fd].zones[0].page = 0x40000000;
	   files[fd].zones[0].sector = files[fd].fat.fstclus + FL_DATA - 2;
	   printc("%d\n",files[fd].zones[0].sector);
	   operation_block(READ, files[fd].zones);	     
	   
	   return 1;
}
void setup_fs()
{
	   int   i;
	   struct Zone zone;
	   
	   /*加载fat目录,9个扇区*/
	   init_Zone(&zone);
	   zone.page = super_block.Fat_sec;	   
	   for(i = 1;i <= 9;i ++)
	   {
	      zone.sector = i;
	      operation_block(READ, &zone);
	      zone.page += 512;	 
	   }

	   /*加载根目录*/
	   init_Zone(&zone);
	   zone.page = super_block.Root_dir;
	   for(i = 1;i <= 14;i ++)
	   {
	      zone.sector = i + 18;
	      operation_block(READ, &zone);
	      zone.page += 512;	 	 
	   }  
}