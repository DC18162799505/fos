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
     
   put_irq_handler(Clock_IRQ, clock_handler);	/* �趨ʱ���жϴ������ */
	 Enable_irq(Clock_IRQ);                     /* ����ʱ���ж�*/
}

void clock_handler(int irq)
{
     current->counts --;
     schedule();
}
