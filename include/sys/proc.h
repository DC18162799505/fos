/*------------------------------------------------------------------------------
   关于进程的信息 
------------------------------------------------------------------------------*/

#ifndef        _PROC_H_
#define        _PROC_H_

#define LDT_SIZE                64

/* 进程的状态 */
#define TASK_RUNNING            0
#define TASK_INTERRUPTIBLE      1
#define TASK_UNINTERRUPTIBLE    2
#define TASK_STOP               3

/* 进程优先级 ：优先级越低，级别越高 */ 
#define Priority_0              0
#define Priority_1              1
#define Priority_2              2
#define Priority_3              3
#define Priority_4              4
#define Priority_6              6

#define P_STACKBASE	0
#define GSREG		0
#define FSREG		4
#define ESREG		8
#define DSREG		12
#define EDIREG		16
#define ESIREG		20
#define EBPREG		    24
#define KERNELESPREG	28
#define EBXREG		32
#define EDXREG		36
#define ECXREG		40
#define EAXREG		44
#define RETADR		48
#define EIPREG		52
#define CSREG		56
#define EFLAGSREG	60
#define ESPREG		64
#define SSREG		68
#define P_STACKTOP	72
#define P_LDT_SEL	72
#define P_LDT		76

typedef struct Task_struct 
{
    /* 信息保存*/
	  struct s_tss        tss;	    		    
	  struct s_descriptor ldts[LDT_SIZE];				
    		           								          
    /* 描述进程的变量 */
    int32               counts;	                 /*信号量*/
    int32               stat;                    /*进程的状态*/
    int32               priority;			           /*进程的优先权*/       
	  int32				        pid;			               /*进程号*/
	  char				        name[16];                /*进程名*/
    
    /*设备*/
    int32               tty_sn;
    
    /*数据*/
    int32               data_start;
    int32               data_end;
    
    /*文件*/
    int                 file_fd;                 /*文件句柄*/
    
    /* 进程的家族关系:采用兄弟树表示 */
    struct Task_struct         *root;
    struct Task_struct         *father;
    struct Task_struct         *brother;
    struct Task_struct         *lastson;
    struct Task_struct         *firstson;

    struct Task_struct         *next;           /*应用于链表*/
}task_struct;

#endif

extern void wait(int *);
extern void signal(int *);
