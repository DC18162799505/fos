#include "type.h"
#include "protect.h"
#include "sys\proc.h"
#include "sys\kernel.h"
#include "sys\sched.h"
#include "sys\system.h"

void schedule()
{
     int32 next,i,max_counts = 0;
     
     while(!max_counts)
     {
          i = NR_TASKS;
          while(i --)
          {
                if((Tasks[i] != NULL) && (Tasks[i]->stat == TASK_RUNNING) && (max_counts < Tasks[i]->counts))
                {
                      max_counts = Tasks[i]->counts;
                      next = i;
                }
          }
          if(!max_counts)
          {
                i = NR_TASKS;
                while(i --)
                {
                      if(Tasks[i] != NULL)
                           Tasks[i]->counts = Tasks[i]->priority;
                }
          }
     }
     switch_to(next);
}

/*通过函数嵌套实现链表操作*/
void sleep_on(struct Task_struct *tem)
{
	   struct Task_struct *pointer;
	   
     pointer = tem;
     tem = current;
     tem -> stat = TASK_INTERRUPTIBLE;
     schedule();
     if(pointer)
         pointer -> stat = TASK_RUNNING;
}

void wake_up(struct Task_struct *tem)
{
	   if(tem)
	   {
	        tem -> stat = TASK_RUNNING;
	        tem = 0;
     }
}
