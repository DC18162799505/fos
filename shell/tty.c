#include       "type.h"
#include       "string.h"
#include       "protect.h"
#include       "fos\memory.h"
#include       "fos\keyboard.h"
#include       "fos\console.h"
#include       "fos\tty.h"
#include       "sys\proc.h"
#include       "sys\kernel.h"

int    init_tty()
{
       int i;
       
       for(i = 0;i < NR_TTY;i ++)
       {
             tty_table[i].begin = tty_table[i].end = tty_table[i].count = 0;
             tty_table[i].console.current_addr = Original_addr * i / 2;
             tty_table[i].console.original_addr = Original_addr * i / 2;
             tty_table[i].console.cursor = Original_addr * i / 2;
             tty_table[i].console.v_mem_limit = tty_table[i].console.original_addr + V_mem / 2;
             tty_table[i].console.console_mem = Video_mm;
             tty_table[i].sn = i;
             tty_table[i].lock = 1;
       }
       
       /*³õÊ¼»¯ÏÔ´æ*/
       for(i = Video_mm;i < 0xC0000;i += 2)
             Phy_mm8[i] = ' ';
       
       current_tty = &tty_table[0];
       
       return 0;
}

void   ctl_tty(int32 key)
{
       if(key >= F1 && key <= F8)
       {
             current_tty = &tty_table[key - F1];
             flush_console(current_tty);
       }
}

void   key_receive(int32 key)
{
       key_encode(key,current_tty); 
}

void   write_tty(struct Tty* p_tty,char *buf,int len)
{
       char *p = buf;
       int  i = len;
       
       while(i)
       {
               switch(*p)
               {
               case '\n':
                    Enter_key(p_tty);
                    break;
               default:
                    console_output(*p,p_tty);
                    break;
               }
               p ++;
               i --;
               
       }
}
