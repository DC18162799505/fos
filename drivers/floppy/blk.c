#include   "type.h"
#include   "string.h"
#include   "IOPort.h"
#include   "protect.h"
#include   "regctl.h"
#include   "sys\proc.h"
#include   "sys\trap.h"
#include   "sys\irq.h"
#include   "fos\dev.h"
#include   "fos\fd.h"
#include   "fos\fs.h"
#include   "sys\kernel.h"
#include   "sys\sched.h"
#include   "fos\blk.h"

void add_request(struct Request * req)
{
    struct Request * tmp;

    req->next = NULL;
    cli();
    if (!(tmp = current_request)) 
    {
        current_request = req;
        sti();
        do_fd_request();
        return;
    }
    /*插入等待队列*/
    while(tmp -> next)
         tmp = tmp -> next;
    tmp -> next = req;
    sti();
}

void lock_buffer(struct Zone * bh)
{
    cli();
    while (bh -> lock)
        sleep_on(bh -> waiting);
    bh -> lock = 1;
    sti();
}

void unlock_buffer(struct Zone * bh)
{
    if (!(bh -> lock))
        printc("ll_rw_block.c: buffer not locked\n\r");
    bh -> lock = 0;
    wake_up(bh -> waiting);
}

void make_request(int rw, struct Zone * bh)
{
	   struct Request *req;
	   
	   req = req_list + get_req();
	   
	   if(rw != READ && rw != WRITE)
	   {
	   	    printc("Bad block dev command,must be R/W!");
	   	    return;
	   }
	   lock_buffer(bh);
	   
	   req -> cmd = rw;
	   req -> errors = 0;
	   req -> block = bh -> sector;
	   req -> nr_sectors = 1;
	   req -> waiting = NULL;
	   req -> buffer = (unsigned long)bh -> page;
	   req -> next = NULL;
	   req -> bh = bh;
	   add_request(req);
}

void operation_block(int rw, struct Zone * bh)
{
	   make_request(rw,bh);
}

/*数据传输完后的处理*/
void end_request(int uptodate)
{
	   current_request -> cmd = -1;
     if (current_request -> bh) 
     {
         current_request -> bh -> uptodata = uptodate;
         unlock_buffer(current_request -> bh);
     }
     if (!uptodate) 
     {
         printk(" I/O error\n");
         printk("dev floppy block %d\n\r",current_request->bh->sector);
     }
     wake_up(&(current_request->waiting));
     current_request = current_request -> next;
}

int get_req()
{
	   int i;
	   
	   for(i = 0;i < NR_REQUEST;i ++)
	   {
	       if(req_list[i].cmd == -1)
	       	    return i;
	   }
	   
	   return -1;
}

void blk_dev_init(void)
{
	   int i;
	   
     current_request = NULL;
     for(i = 0;i < NR_REQUEST;i ++)
          req_list[i].cmd = -1;          
}
