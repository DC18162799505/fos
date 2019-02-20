/*------------------------------------------------------------------------------
   常量 
------------------------------------------------------------------------------*/

#ifndef        _KERNEL_H_
#define        _KERNEL_H_

/* GDT 和 IDT 中描述符的个数 */
#define	GDT_SIZE	256
#define	IDT_SIZE	256

/* Number of tasks */
#define NR_TASKS	63

/* 页目录基址 */
#define PageDirBase 0x100000 
/* 页表基址   */
#define PageTabBase 0x101000     

/* 堆栈顶*/
#define      Kernel_SS       0x40000000                    /*1G*/
#define      User_SS         0xFFFFFFFC                    /*4G-4*/

/* 进程0的选择子 */ 
#define    Selector_dump         0x0
#define    Selector_kernel_cs    0x8
#define    Selector_kernel_ds    0x10
#define    Selector_Video        0x18  

/* 进程0的选择子的索引 */
#define    Dump_index            0
#define    Kernel_cs_index       1
#define    Kernel_ds_index       2
#define    Video_index           3
#define    Tss_index             4
#define    Ldt_index             5                /*用于处理操作系统自己私有的*/
           
#endif

struct Task_struct  *current;
struct Task_struct  *Tasks[NR_TASKS];
struct Task_struct  init_task;

/*-----------变量-------------------------------------------------------------*/
struct GDT           Gdtptr;              
struct IDT           Idtptr;              
struct s_descriptor  *Gdt;                /*全局描述符表*/
struct s_gate        *Idt;                /*中断描述符表*/

extern void  jmp_user();                  /*跳转至应用程序*/
extern void  call_user();                 /*调用应用程序*/ 
	
extern void task_init();
extern char* getpname();
extern int getid();
extern int init_kernel();
