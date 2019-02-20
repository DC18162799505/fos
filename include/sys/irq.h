/*------------------------------------------------------------------------------
   关于8259A的头文件 
------------------------------------------------------------------------------*/

#ifndef      _IRQ_H_
#define      _IRQ_H_

#define	INT_VECTOR_IRQ0			   0x20
#define	INT_VECTOR_IRQ8			   0x28

#define STI_IRQ         0xfd              /*键盘中断*/

#define	NR_IRQ		      16	
#define	Clock_IRQ	      0
#define	Keyboard_IRQ	  1
#define Slave_IRQ       2
#define	Serial2_IRQ	    3	
#define	Serial1_IRQ	    4	
#define	Lpt2_IRQ    	  5	
#define	Floppy_IRQ	    6	
#define	Lpt1_IRQ	      7	
#define	Real_IRQ	      8	
#define	Mouse_IRQ	      0xc
#define	Fpu_IRQ	        0xD	
#define	Atwin_IRQ	      0xE	

/*master 8259A*/
#define  IRQ0_time      0x20
#define  IRQ1_keyboard  0x21
#define  IRQ2_slave     0x22
#define  IRQ3_serial2   0x23
#define  IRQ4_serial1   0x24
#define  IRQ5_lpt2      0x25
#define  IRQ6_floppy    0x26
#define  IRQ7_lpt1      0x27
/*slave 8259A*/
#define  IRQ8_real      0x28
#define  IRQ9_IRQ2      0x29
#define  IRQ10_reserved 0x2A
#define  IRQ11_reserved 0x2B
#define  IRQ12_mouse    0x2C
#define  IRQ13_fpu      0x2D
#define  IRQ14_atwin    0x2E
#define  IRQ15_reserved 0x2F

#endif
/*-irq中断表------------------------------------------------------------------*/
irq_handler    irq_table[NR_IRQ];
/*----------------------------------------------------------------------------*/
/* 8259A中断处理函数*/
extern void     super_irq(int);

extern void     Timer_intr();
extern void     Kerboard_intr();
extern void     Serial2_intr();
extern void     Serial1_intr();
extern void     Lpt2_intr();
extern void     Floppy_intr();
extern void     Lpt1_intr();

extern void     Real_intr();
extern void     Mouse_intr();
extern void     Fpu_intr();
extern void     Atwin_intr();
/*----------------------------------------------------------------------------*/
extern void     Disable_irq(int irq);                      /*关闭中断*/
extern void     Enable_irq(int irq);                       /*开启中断*/
extern int      init_irq();
extern void     put_irq_handler(int,irq_handler);
