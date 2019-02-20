
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            protect.h
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#ifndef	_PROTECT_H_
#define	_PROTECT_H_


/* �洢��������/ϵͳ�������� */
typedef struct s_descriptor		/* �� 8 ���ֽ� */
{
	int16	limit_low;		/* Limit */
	int16	base_low;		/* Base */
	int8	base_mid;		/* Base */
	int8	attr1;			/* P(1) DPL(2) DT(1) TYPE(4) */
	int8	limit_high_attr2;	/* G(1) D(1) 0(1) AVL(1) LimitHigh(4) */
	int8	base_high;		/* Base */
}DESCRIPTOR;


/* �������� */
typedef struct s_gate
{
	int16	offset_low;	       /* Offset Low */
	int16	selector;	       /* Selector */
	int8	dcount;		       /* ���ֶ�ֻ�ڵ���������������Ч��
				                 ��������õ����ŵ����ӳ���ʱ������Ȩ����ת���Ͷ�ջ�ĸı䣬
                         ��Ҫ������ջ�еĲ������Ƶ��ڲ��ջ��
				                 ��˫�ּ����ֶξ�������˵�������������ʱ��
                         Ҫ���Ƶ�˫�ֲ����������� */
	int8	attr;		         /* P(1) DPL(2) DT(1) TYPE(4) */
	int16	offset_high;	   /* Offset High */
}GATE;

/* ����������  */ 
typedef struct s_tss {
	int32	backlink;
	int32	esp0;		      /* stack pointer to use during interrupt */
	int32	ss0;		      /*   "   segment  "  "    "        "     */
	int32	esp1;
	int32	ss1;
	int32	esp2;
	int32	ss2;
	int32	cr3;
	int32	eip;
	int32	flags;
	int32	eax;
	int32	ecx;
	int32	edx;
	int32	ebx;
	int32	esp;
	int32	ebp;
	int32	esi;
	int32	edi;
	int32	es;
	int32	cs;
	int32	ss;
	int32	ds;
	int32	fs;
	int32	gs;
	int32	ldt;
	int16	trap;
	int16	iobase;	/* I/Oλͼ��ַ���ڻ����TSS�ν��ޣ��ͱ�ʾû��I/O���λͼ */
	int16   end;
}TSS;

/* ȫ���������ṹ*/
typedef struct GDT
{
      int32 limite;
      int32 base;
}Gdt_Ptr;

/* �ж��������ṹ*/
typedef struct IDT
{
      int32 limite;
      int32 base;
}Idt_Ptr;

/* ��������Ȩ�� */ 
#define    DA_32         0x4000        /*  32 BITS CODE  */
#define    DA_LIMIT_4K	 0x8000	      /*  page size     */

#define    DA_DPL0         0x00          /*  DPL = 0       */
#define    DA_DPL1         0x20          /*  DPL = 1       */
#define    DA_DPL2         0x40          /*  DPL = 2       */
#define    DA_DPL3         0x60          /*  DPL = 3       */
/* ����������  */ 
#define    DA_D_R          0x90          /*  DATA DES WITH ONLY READ                   */
#define    DA_D_RW         0x92          /*  DATA DES WITH READ AND WRITE              */
#define    DA_D_RWA        0x93          /*  DATA DES WITH READ , WRITE AND ACCESSED   */
#define    DA_E_           0x98          /*  CODE DES                                  */
#define    DA_E_R          0x9A          /*  CODE DES WITH READ                        */
#define    DA_E_C          0x9C          /*  CODE DES WITH CO CODE                     */
#define    DA_E_E          0x9E          /*  CODE DES WITH CO CODE , READ              */

/* ϵͳ������������ */ 
#define    DA_S_LDT        0x82          /*   LOCAL DESCRIPTOR                       */
#define    DA_S_TG         0x85          /*   TASK GATE                              */
#define    DA_S_386TSS     0x89          /*   STATUS OF TASK                         */
#define    DA_S_386CGATE   0x8C          /*   CALL GATE                              */
#define    DA_S_386IGATE   0x8E          /*   INTERRUPT GATE                         */
#define    DA_S_386TGATE   0x8F          /*   TRAP GATE                              */

/* ѡ����  */ 
#define    SA_RPL0         0x00          /*   RPL = 0                                */
#define    SA_RPL1         0x01          /*   RPL = 1                                */ 
#define    SA_RPL2         0x02          /*   RPL = 2                                */
#define    SA_RPL3         0x03          /*   PRL = 4                                */

#define    SA_TIL          0x04          /*   LOCAL                                  */
#define    SA_TIG          0x00          /*   GLOBA                                  */

/* ҳ����  */ 
#define    PG_P		       1	        /*   PRESENT BIT                            */
#define    PG_RW_R		   0	        /*   R/W READ AND EXECUTE                   */
#define    PG_RW_W		   2	        /*   R/W READ, EXECUTE AND WRITE            */
#define    PG_US_S		   0	        /*   U/S SUPERVISOR                         */ 
#define    PG_US_U		   4	        /*   U/S USER                               */


/* ��Ȩ�� */
#define    Privilege_kernel      0x0
#define    Privilege_user        0x3  
#endif

extern int Ptrctl(int32 *va,int32 *vb);     /* ������������Ϣ */
extern int set_descriptor(DESCRIPTOR * p_desc, int32 base, int32 limit, int16 attribute);
                                            /* ������������Ϣ */
extern int set_idt_desc(int32 vector, int32 desc_type, int_handler handler, int32 privilege);
                                            /* ��ʼ���ж������� */
extern int32 seg2phys(int16 seg);           /* �ɶ�������Ե�ַ */
