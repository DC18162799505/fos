#ifndef       _SCHED_H_
#define       _SCHED_H_

#endif

extern void schedule();                                   /*调度程序*/
extern void sleep_on(struct Task_struct *tem);            /*睡眠程序*/
extern void wake_up(struct Task_struct *tem);             /*唤醒程序*/
