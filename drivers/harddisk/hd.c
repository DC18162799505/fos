#include   "type.h"
#include   "string.h"
#include   "IOPort.h"
#include   "protect.h"
#include   "regctl.h"
#include   "sys\proc.h"
#include   "sys\trap.h"
#include   "sys\irq.h"
#include   "fos\blk.h"
#include   "fos\hd.h"
#include   "sys\kernel.h"

int controller_ready()
{
    int retries=10000;

    while (--retries && (inb(HD_STATUS)&0xc0)!=0x40);
    return (retries);
}

int win_result()
{
    int tem = inb(HD_STATUS);

    if ((tem & (BUSY_STAT | READY_STAT | WRERR_STAT | SEEK_STAT | ERR_STAT)) == (READY_STAT | SEEK_STAT))
        return(0); /* ok */
    if (tem & 1) tem = inb(HD_ERROR);
    return (1);
}

int drive_busy(void)
{
    int i,tem;

    for (i = 0; i < 10000; i++)
    {
        if (READY_STAT == (inb(HD_STATUS) & (BUSY_STAT|READY_STAT)))
            break;
    }
    tem = inb(HD_STATUS);
    tem &= BUSY_STAT | READY_STAT | SEEK_STAT;
    if (tem == (READY_STAT | SEEK_STAT))
        return(0);
    printc("HD controller times out\n\r");

    return(1);
}

void init_hd()
{
     put_irq_handler(Atwin_IRQ, hd_handler);	/* 设定硬盘中断处理程序 */
	 Enable_irq(Atwin_IRQ);                     /* 开启硬盘中断*/     
}
