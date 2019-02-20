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

/* ----------- ��ȡϵͳʱ�� --------------------------------------------------*/ 

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
	  /*�����ļ���Ϣ*/
	  printc("turn into setup_fs!\n");
	  setup_fs();
	  printc("setup fs succeed!\n");
}
int cmain(void)
{	   
	  /*�����ں˴�ӡ����*/
	  dispos = 0;
	  v_array = 0xB8000;
	  
    /* ��ȡ�ж����������ȫ������������Ϣ*/
    Sidt_call(&Idtptr);
    Ptrctl(&Idtptr.base,&Idtptr.limite);
    Sgdt_call(&Gdtptr);
    Ptrctl(&Gdtptr.base,&Gdtptr.limite);
    Gdt = Gdtptr.base;
    Idt = Idtptr.base;
    
    init_time();              /*��ȡϵͳʱ��*/

    /*�ڴ��ʼ��*/    
    init_mm();
    /*�жϳ�ʼ��*/
    init_idt();
    init_irq();
    blk_dev_init();
    init_sys_call();
    /*��ʼ������̨*/
    init_tty();
    /*����0��ʼ��*/
    init_kernel(); 
    /*�ļ�ϵͳ��ʼ��*/
    init_fs();
    
   	/*ת���û�ģʽDPL3��ͬʱ����Ӳ���жϣ���IOL��Ϊ3*/
   	/*note:Ӳ���ж�Ӧ����move_to_user_mode()�п�����������п��ܳ��ֲ������ϵĴ���*/
    move_to_user_mode();
    
    init();
    
    /*�������ӡ�
    ���������ͨ��fork()�����������������̣�Ҳ�����ܹ�����������
    һ�������Ǵ����̼���Ӧ�ó��򣬲����и�Ӧ�ó���
    �ڶ�������������ѭ��������printc("testA: %d\n",num ++);��䣬
    ���������������������м�����������*/
    
    fork();
    if(1 == getid())
    {
    	  /*�л�������һ����Ļ*/
    	  current -> tty_sn = 1;
    	  /*�����̼���test.bin�ļ�*/
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

