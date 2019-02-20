#include   "type.h"
#include   "string.h"
#include   "IOPort.h"
#include   "protect.h"
#include   "regctl.h"
#include   "sys\proc.h"
#include   "sys\trap.h"
#include   "sys\irq.h"
#include   "fos\dev.h"
#include   "fos\blk.h"
#include   "fos\hd.h"
#include   "sys\kernel.h"

struct request request[NR_REQUEST];
struct Task_struct *wait_for_request = NULL;
struct blk_dev_struct blk_dev[NR_BLK_DEV] = {
    { NULL, NULL },     /* no_dev */
    { NULL, NULL },     /* dev mem */
    { NULL, NULL },     /* dev fd */
    { NULL, NULL },     /* dev hd */
    { NULL, NULL },     /* dev ttyx */
    { NULL, NULL },     /* dev tty */
    { NULL, NULL }      /* dev lp */
};

void add_request(struct blk_dev_struct * dev, struct request * req)
{
    struct request * tmp;

    req->next = NULL;
    cli();
    if (!(tmp = dev->current_request)) 
    {
        dev->current_request = req;
        sti();
        (dev->request_fn)();
        return;
    }
    while(tmp -> next)
         tmp = tmp -> next;
    tmp -> next = req;
    sti();
}

void blk_dev_init(void)
{
    int i;

    for (i=0 ; i<NR_REQUEST ; i++) 
    {
        request[i].dev = No_dev;
        request[i].next = NULL;
    }
}

