#include  "type.h"
#include  "protect.h"
#include  "regctl.h"
#include  "sys\trap.h"
#include  "string.h"
#include  "fos\memory.h"

char err_description[][64] = {	
                    "#DE Divide Error",
					"#DB RESERVED",
					"—  NMI Interrupt",
					"#BP Breakpoint",
					"#OF Overflow",
					"#BR BOUND Range Exceeded",
					"#UD Invalid Opcode (Undefined Opcode)",
					"#NM Device Not Available (No Math Coprocessor)",
					"#DF Double Fault$",
					"    Coprocessor Segment Overrun (reserved)",
					"#TS Invalid TSS",
					"#NP Segment Not Present",
					"#SS Stack-Segment Fault",
					"#GP General Protection",
					"#PF Page Fault$",
					"—  (Intel reserved. Do not use.)",
					"#MF x87 FPU Floating-Point Error (Math Fault)",
					"#AC Alignment Check",
					"#MC Machine Check",
					"#XF SIMD Floating-Point Exception"
				};
				
int init_idt()
{
	set_idt_desc(INT_VECTOR_DIVIDE,DA_S_386TGATE,divide_error,Privilege_kernel);
	set_idt_desc(INT_VECTOR_DEBUG,DA_S_386TGATE,single_step_exception,Privilege_kernel);
	set_idt_desc(INT_VECTOR_NMI,DA_S_386IGATE,nmi,Privilege_kernel);
	set_idt_desc(INT_VECTOR_BREAKPOINT,DA_S_386TGATE,breakpoint_exception,Privilege_user);
	set_idt_desc(INT_VECTOR_OVERFLOW,DA_S_386TGATE, overflow,Privilege_user);
	set_idt_desc(INT_VECTOR_BOUNDS,DA_S_386TGATE, bounds_check,Privilege_user);
	set_idt_desc(INT_VECTOR_INVAL_OP,DA_S_386TGATE, inval_opcode,Privilege_kernel);
	set_idt_desc(INT_VECTOR_COPROC_NOT,DA_S_386TGATE, copr_not_available,Privilege_kernel);
	set_idt_desc(INT_VECTOR_DOUBLE_FAULT,DA_S_386TGATE, double_fault,Privilege_kernel);
	set_idt_desc(INT_VECTOR_COPROC_SEG,DA_S_386TGATE, copr_seg_overrun,Privilege_kernel);
	set_idt_desc(INT_VECTOR_INVAL_TSS,DA_S_386TGATE, inval_tss,Privilege_kernel);
	set_idt_desc(INT_VECTOR_SEG_NOT,DA_S_386TGATE, segment_not_present,Privilege_kernel);
	set_idt_desc(INT_VECTOR_STACK_FAULT,DA_S_386TGATE, stack_exception,Privilege_kernel);
	set_idt_desc(INT_VECTOR_PROTECTION,DA_S_386TGATE, general_protection,Privilege_kernel);
	set_idt_desc(INT_VECTOR_PAGE_FAULT,DA_S_386TGATE, page_fault,Privilege_kernel);
	set_idt_desc(INT_VECTOR_COPROC_ERR,DA_S_386TGATE, copr_error,Privilege_kernel);
	  
    return 0;
}

void super_handler(int vec_no, int err_code, int eip, int cs, int eflags)
{
	/* 通过打印空格的方式清空屏幕的前五行，并把 disp_pos 清零 */
	switch(vec_no)
	{
         case INT_VECTOR_DIVIDE:
         case INT_VECTOR_DEBUG:
         case INT_VECTOR_NMI:
         case INT_VECTOR_BREAKPOINT:
         case INT_VECTOR_OVERFLOW:
         case INT_VECTOR_BOUNDS:
         case INT_VECTOR_INVAL_OP:
         case INT_VECTOR_COPROC_NOT:
         case INT_VECTOR_DOUBLE_FAULT:
         case INT_VECTOR_COPROC_SEG:
         case INT_VECTOR_INVAL_TSS:
         case INT_VECTOR_SEG_NOT:
         case INT_VECTOR_STACK_FAULT:
         case INT_VECTOR_PROTECTION:
              printk("%s :\n",err_description[vec_no]);
              printk("eip = %d\n",eip);
              printk("cs  = %d\n",cs);
              printk("eflags  = %d\n",eflags);
	          if(err_code != 0xFFFFFFFF)
                    printk("err_code = %d\n",err_code);
              break;
         case INT_VECTOR_PAGE_FAULT:
              do_page(get_cr2_long(),err_code);
              break;
         case INT_VECTOR_COPROC_ERR:
         default:
                 printk("An unknown excetion!\n");
                 break;
    }
}
