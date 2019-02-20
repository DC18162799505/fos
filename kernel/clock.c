#include "type.h"
#include "string.h"
#include "protect.h"
#include "regctl.h"
#include "IOPort.h"
#include "fos\memory.h"
#include "sys\trap.h"
#include "sys\irq.h"
#include "sys\clock.h"
#include "sys\sched.h"
#include "sys\proc.h"
#include "sys\kernel.h"

void init_clock()
{
   outb(TIMER_CTL_IN, TIMER0_MODE);
	 outb(TIMER0_IN, (int8) (TIMER_FREQ/TIMER0_MODE) );
	 outb(TIMER0_IN, (int8) ((TIMER_FREQ/TIMER0_MODE) >> 8));
     
   put_irq_handler(Clock_IRQ, clock_handler);	/* 设定时钟中断处理程序 */
	 Enable_irq(Clock_IRQ);                     /* 开启时钟中断*/
}

void clock_handler(int irq)
{
     current->counts --;
     schedule();
}
