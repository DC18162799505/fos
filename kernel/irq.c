#include  "type.h"
#include  "sys\irq.h"
#include  "sys\clock.h"
#include  "string.h"
#include  "protect.h"
#include  "fos\keyboard.h"
#include  "fos\fd.h"
#include  "IOPort.h"

void super_irq(int irq_no)
{
     printc("IRQ_NO: %d\n",irq_no);
}

int init_irq()
{
    /*中断描述符表初始化*/
	set_idt_desc(IRQ0_time,DA_S_386IGATE,Timer_intr,Privilege_kernel);
	set_idt_desc(IRQ1_keyboard,DA_S_386IGATE,Kerboard_intr,Privilege_kernel);
	set_idt_desc(IRQ3_serial2,DA_S_386IGATE,Serial2_intr,Privilege_kernel);
	set_idt_desc(IRQ4_serial1,DA_S_386IGATE,Serial1_intr,Privilege_kernel);
	set_idt_desc(IRQ5_lpt2,DA_S_386IGATE,Lpt2_intr,Privilege_kernel);
	set_idt_desc(IRQ6_floppy,DA_S_386IGATE,Floppy_intr,Privilege_kernel);
	set_idt_desc(IRQ7_lpt1,DA_S_386IGATE,Lpt1_intr,Privilege_kernel);
	set_idt_desc(IRQ8_real,DA_S_386IGATE,Real_intr,Privilege_kernel);
	set_idt_desc(IRQ12_mouse,DA_S_386IGATE,Mouse_intr,Privilege_kernel);
	set_idt_desc(IRQ13_fpu,DA_S_386IGATE,Fpu_intr,Privilege_kernel);
	set_idt_desc(IRQ14_atwin,DA_S_386IGATE,Atwin_intr,Privilege_kernel);
	
	/*8259A中断处理函数*/
  init_clock();                /*时钟初始化*/
	key_init();                  /*键盘初始化*/
  init_fd();                   /*软盘初始化*/
  
  return 0;
}

void put_irq_handler(int irq, irq_handler handler)
{
	irq_table[irq] = handler;
}
