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
#include   "test.h"

/* ----------- 获取系统时间 --------------------------------------------------*/ 

int init_time()
{
    outb(CMOS_OUT,TIME_SYSTEM_SECOND);
    Time.sec = inb(CMOS_IN);
    outb(CMOS_OUT,TIME_SYSTEM_MINUTE);
    Time.min = inb(CMOS_IN);
    outb(CMOS_OUT,TIME_SYSTEM_HOUR);
    Time.hour = inb(CMOS_IN);  
    outb(CMOS_OUT,TIME_SYSTEM_WEEK);
    Time.week = inb(CMOS_IN);
    outb(CMOS_OUT,TIME_SYSTEM_DATE);
    Time.data = inb(CMOS_IN);
    outb(CMOS_OUT,TIME_SYSTEM_MONTH);
    Time.month = inb(CMOS_IN);
    outb(CMOS_OUT,TIME_SYSTEM_YEAR);
    Time.year = inb(CMOS_IN);
    BCD_TO_BIN(Time.sec);
    BCD_TO_BIN(Time.min);
    BCD_TO_BIN(Time.hour);
    BCD_TO_BIN(Time.week);
    BCD_TO_BIN(Time.data);
    BCD_TO_BIN(Time.month);
    BCD_TO_BIN(Time.year);
    return 0;
}
void init()
{
	  /*加载文件信息*/
	  printc("turn into setup_fs!\n");
	  setup_fs();
	  printc("setup fs succeed!\n");
}
int cmain(void)
{	   
	  /*用于内核打印函数*/
	  dispos = 0;
	  v_array = 0xB8000;
	  
    /* 获取中断描述符表和全局描述符表信息*/
    Sidt_call(&Idtptr);
    Ptrctl(&Idtptr.base,&Idtptr.limite);
    Sgdt_call(&Gdtptr);
    Ptrctl(&Gdtptr.base,&Gdtptr.limite);
    Gdt = Gdtptr.base;
    Idt = Idtptr.base;
    
    init_time();              /*获取系统时间*/

    /*内存初始化*/    
    init_mm();
    /*中断初始化*/
    init_idt();
    init_irq();
    blk_dev_init();
    init_sys_call();
    /*初始化控制台*/
    init_tty();
    /*进程0初始化*/
    init_kernel(); 
    /*文件系统初始化*/
    init_fs();
    
   	/*转入用户模式DPL3，同时开启硬件中断，把IOL设为3*/
   	/*note:硬件中断应该在move_to_user_mode()中开启，否则很有可能出现不可意料的错误*/
    move_to_user_mode();
    
    init();
    
    /*测试例子。
    在这里，我们通过fork()函数创建了两个进程，也就是总共有三个进程
    一个进程是从软盘加载应用程序，并运行该应用程序，
    第二个进程则是死循环，运行printc("testA: %d\n",num ++);语句，
    第三个进程则是则是运行键盘驱动程序*/
    
    fork();
    if(1 == getid())
    {
    	  /*切换到另外一个屏幕*/
    	  current -> tty_sn = 1;
    	  /*从软盘加载test.bin文件*/
	      load_file("TEST1.BIN");
	      code = 0x40000000;
	      /*code[0] = 0xC3;*/
	      printc("load fs succeed!\n");
	      fork();
	      if(3 == getid())
	      {
	      	   current -> tty_sn = 2;
	      	   call_user();
	      	   while(1)
	      	        printc("process3\n");
	      }
	      else
	      {
	      	    fork();
	      	    if(4 == getid())
	      	    {
	      	    	   current -> tty_sn = 3;
	                 /*load_file("TEST0.BIN");*/
	                 printc("load fs succeed!\n");
	                 /*while(1);*/
	                 code[0] = 0xeb;
	                 code[1] = 0xfe;
	                 call_user();
	      	    	   while(1)
	      	    	        printc("process4\n");
	      	    }
	      	    else
	      	    {
    		           call_user();
    	             while(1)
    	                  printc("process1\n");
    	        }
    	  }
    }
    else
    {
    	  fork();
    	  if(2 == getid())
    	  {
    	  	  while(1)
    	          printc("process0\n");
    	  }
    	  else
    	  {
    	  	  while(1)
                keyboard_read();
    	  }
    }

    while(1);
    return 0;
}

