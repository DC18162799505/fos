#include   "type.h"
#include   "protect.h"
#include   "fos\console.h"
#include   "fos\tty.h"
#include   "sys\proc.h"
#include   "sys\kernel.h"
#include   "fos\sys.h"

int  sys_write(char* buf,int len,struct Task_struct *p_task)
{
     wait(&(tty_table[p_task->tty_sn].lock));
     write_tty(&tty_table[p_task->tty_sn],buf,len);
     signal(&(tty_table[p_task->tty_sn].lock));
     return 0;
}
