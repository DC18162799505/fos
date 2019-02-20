/*------------------------------------------------------------------------------
   关于时钟的头文件 
------------------------------------------------------------------------------*/

#ifndef      _CLOCK_H_
#define      _CLOCK_H_

#define TIMER0_MODE	0x34	     /* 00-11-010-0 : Counter0 - LSB then MSB - rate generator - binary*/
#define TIMER_FREQ	1193182L     /* clock frequency for timer in PC and AT */
#define SCH_HZ		100	         /* clock freq (software settable on IBM-PC) */

#endif

extern void init_clock();
extern void clock_handler(int irq);
