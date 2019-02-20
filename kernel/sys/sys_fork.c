#include   "type.h"
#include   "string.h"
#include   "IOPort.h"
#include   "time.h"
#include   "protect.h"
#include   "sys\trap.h"
#include   "regctl.h"
#include   "sys\irq.h"
#include   "fos\sys.h"
#include   "fos\memory.h"
#include   "sys\system.h"
#include   "fos\keyboard.h"
#include   "fos\console.h"
#include   "fos\tty.h"
#include   "sys\proc.h"
#include   "sys\kernel.h"
#include   "fos\fs.h"

int find_empty_process()
{
	  int i;
	  
	  for(i = 0;i < NR_TASKS;i ++)
	  {
	  	   if(!Tasks[i])
	  	   	    return i;
	  }
	  return 0;
}

int sys_fork(long para1,long para2,long para3,long addr,long gs,long fs,long es,long ds,
             long edi,long esi,long ebp,long esp,long ebx,long edx,long ecx,long eax,
             long addr_save,long eip,long cs,long flags,long esp3,long ss3)
{
	  long new_cr3,old_cr3;
	  int nr;
	  struct Task_struct *p;
	  
	  nr = find_empty_process();
	  p = get_free_app() << 12;
	  Tasks[nr] = p;
	  
	  *p = *current;
	  p -> stat = TASK_INTERRUPTIBLE;
	  p -> pid = nr;
	  p -> counts = 10;
	  
	  /*初始化任务描述符*/
	  p -> tss.backlink = 0;	 

    /*处理页表*/
    old_cr3 = get_cr3_long();
	  new_cr3 = pg2add8(get_free_app());	  
	  p -> tss.cr3 = new_cr3;
    copy_page_tables(old_cr3,new_cr3);

	  /*初始化内核的时候也申请一页做为内核堆栈*/
	  p -> tss.esp0 = Kernel_SS;
	  put_page(new_cr3,pg2add8(get_free_app()),Kernel_SS - 1);
	  p -> tss.ss0 = Selector_kernel_ds;
	  
    /*处理寄存器保存区*/
	  p -> tss.eip = eip;
	  p -> tss.flags = flags;
	  p -> tss.eax = eax;
	  p -> tss.ecx = ecx;
	  p -> tss.edx = edx;
	  p -> tss.ebx = ebx;
	  p -> tss.esp = esp3;
	  p -> tss.ebp = ebp;
	  p -> tss.esi = esi;
	  p -> tss.edi = edi;
	  p -> tss.es = es;
	  p -> tss.cs = cs;
	  p -> tss.ss = ss3;
	  p -> tss.ds = ds;
	  p -> tss.fs = fs;
	  p -> tss.gs = gs;
	  
	  p -> tss.ldt = LDT(nr);                             /*选择子*/
	  
	  set_descriptor(&Gdt[TSS_INDEX(nr)],(int32)&(p -> tss),sizeof(p -> tss) - 1,DA_S_386TSS | DA_DPL3);
	  set_descriptor(&Gdt[LDT_INDEX(nr)],(int32)(p ->ldts),LDT_SIZE * 8,DA_S_LDT);
	  
	  p -> stat = TASK_RUNNING; 
	  return nr;
}