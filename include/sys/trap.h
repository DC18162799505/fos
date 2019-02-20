/*------------------------------------------------------------------------------
   �����жϵ�ͷ�ļ� 
------------------------------------------------------------------------------*/

#ifndef      _TRAP_H_
#define      _TRAP_H_

/* �ж����� */
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
#define INT_VECTOR_RESERVED        0xF            /*intel ���� */
#define	INT_VECTOR_COPROC_ERR	   0x10

#endif

extern char err_description[][64];
/*--------�����жϵĺ���------------------------------------------------------*/
extern void super_handler(int vec_no, int err_code, int eip, int cs, int eflags);
                                            /* ���ڳ�ʼ���ж�������  */ 
extern void	divide_error();                 /* �������� */
extern void	single_step_exception();        /* �����쳣 */ 
extern void	nmi();                          /* ���������ж� */
extern void	breakpoint_exception();         /* ���ֽ�int3 */
extern void	overflow();                     /* ��� */
extern void	bounds_check();                 /* �߽��� */
extern void	inval_opcode();                 /* �Ƿ������� */
extern void	copr_not_available();           /* �豸������ */
extern void	double_fault();                 /* ˫�ز��� */
extern void	copr_seg_overrun();             /* Э��������Խ�� */
extern void	inval_tss();                    /* ��ЧTSS�쳣 */
extern void	segment_not_present();          /* �β����� */
extern void	stack_exception();              /* �ζ�ջ�쳣 */
extern void	general_protection();           /* ͨ�ñ����쳣 */
extern void	page_fault();                   /* ҳ�쳣 */
extern void	copr_error();                   /* Э���������� */
/*----------------------------------------------------------------------------*/

extern int init_idt();         /* ��ʼ���ж��������� */ 

