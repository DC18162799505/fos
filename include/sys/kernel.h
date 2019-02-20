/*------------------------------------------------------------------------------
   ���� 
------------------------------------------------------------------------------*/

#ifndef        _KERNEL_H_
#define        _KERNEL_H_

/* GDT �� IDT ���������ĸ��� */
#define	GDT_SIZE	256
#define	IDT_SIZE	256

/* Number of tasks */
#define NR_TASKS	63

/* ҳĿ¼��ַ */
#define PageDirBase 0x100000 
/* ҳ���ַ   */
#define PageTabBase 0x101000     

/* ��ջ��*/
#define      Kernel_SS       0x40000000                    /*1G*/
#define      User_SS         0xFFFFFFFC                    /*4G-4*/

/* ����0��ѡ���� */ 
#define    Selector_dump         0x0
#define    Selector_kernel_cs    0x8
#define    Selector_kernel_ds    0x10
#define    Selector_Video        0x18  

/* ����0��ѡ���ӵ����� */
#define    Dump_index            0
#define    Kernel_cs_index       1
#define    Kernel_ds_index       2
#define    Video_index           3
#define    Tss_index             4
#define    Ldt_index             5                /*���ڴ������ϵͳ�Լ�˽�е�*/
           
#endif

struct Task_struct  *current;
struct Task_struct  *Tasks[NR_TASKS];
struct Task_struct  init_task;

/*-----------����-------------------------------------------------------------*/
struct GDT           Gdtptr;              
struct IDT           Idtptr;              
struct s_descriptor  *Gdt;                /*ȫ����������*/
struct s_gate        *Idt;                /*�ж���������*/

extern void  jmp_user();                  /*��ת��Ӧ�ó���*/
extern void  call_user();                 /*����Ӧ�ó���*/ 
	
extern void task_init();
extern char* getpname();
extern int getid();
extern int init_kernel();
