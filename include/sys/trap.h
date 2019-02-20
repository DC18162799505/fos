/*------------------------------------------------------------------------------
   关于中断的头文件 
------------------------------------------------------------------------------*/

#ifndef      _TRAP_H_
#define      _TRAP_H_

/* 中断向量 */
#define	INT_VECTOR_DIVIDE		   0x0
#define	INT_VECTOR_DEBUG		   0x1
#define	INT_VECTOR_NMI			   0x2
#define	INT_VECTOR_BREAKPOINT	   0x3
#define	INT_VECTOR_OVERFLOW		   0x4
#define	INT_VECTOR_BOUNDS		   0x5
#define	INT_VECTOR_INVAL_OP		   0x6
#define	INT_VECTOR_COPROC_NOT	   0x7
#define	INT_VECTOR_DOUBLE_FAULT	   0x8
#define	INT_VECTOR_COPROC_SEG	   0x9
#define	INT_VECTOR_INVAL_TSS	   0xA
#define	INT_VECTOR_SEG_NOT		   0xB
#define	INT_VECTOR_STACK_FAULT	   0xC
#define	INT_VECTOR_PROTECTION	   0xD
#define	INT_VECTOR_PAGE_FAULT	   0xE
#define INT_VECTOR_RESERVED        0xF            /*intel 保留 */
#define	INT_VECTOR_COPROC_ERR	   0x10

#endif

extern char err_description[][64];
/*--------处理中断的函数------------------------------------------------------*/
extern void super_handler(int vec_no, int err_code, int eip, int cs, int eflags);
                                            /* 用于初始化中断描述符  */ 
extern void	divide_error();                 /* 除法错误 */
extern void	single_step_exception();        /* 调试异常 */ 
extern void	nmi();                          /* 不可屏蔽中断 */
extern void	breakpoint_exception();         /* 单字节int3 */
extern void	overflow();                     /* 溢出 */
extern void	bounds_check();                 /* 边界检查 */
extern void	inval_opcode();                 /* 非法操作码 */
extern void	copr_not_available();           /* 设备不可用 */
extern void	double_fault();                 /* 双重操作 */
extern void	copr_seg_overrun();             /* 协处理器段越界 */
extern void	inval_tss();                    /* 无效TSS异常 */
extern void	segment_not_present();          /* 段不存在 */
extern void	stack_exception();              /* 段堆栈异常 */
extern void	general_protection();           /* 通用保护异常 */
extern void	page_fault();                   /* 页异常 */
extern void	copr_error();                   /* 协处理器出错 */
/*----------------------------------------------------------------------------*/

extern int init_idt();         /* 初始化中断描述符表 */ 

