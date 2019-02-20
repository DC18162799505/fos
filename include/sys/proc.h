/*------------------------------------------------------------------------------
   ���ڽ��̵���Ϣ 
------------------------------------------------------------------------------*/

#ifndef        _PROC_H_
#define        _PROC_H_

#define LDT_SIZE                64

/* ���̵�״̬ */
#define TASK_RUNNING            0
#define TASK_INTERRUPTIBLE      1
#define TASK_UNINTERRUPTIBLE    2
#define TASK_STOP               3

/* �������ȼ� �����ȼ�Խ�ͣ�����Խ�� */ 
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
    /* ��Ϣ����*/
	  struct s_tss        tss;	    		    
	  struct s_descriptor ldts[LDT_SIZE];				
    		           								          
    /* �������̵ı��� */
    int32               counts;	                 /*�ź���*/
    int32               stat;                    /*���̵�״̬*/
    int32               priority;			           /*���̵�����Ȩ*/       
	  int32				        pid;			               /*���̺�*/
	  char				        name[16];                /*������*/
    
    /*�豸*/
    int32               tty_sn;
    
    /*����*/
    int32               data_start;
    int32               data_end;
    
    /*�ļ�*/
    int                 file_fd;                 /*�ļ����*/
    
    /* ���̵ļ����ϵ:�����ֵ�����ʾ */
    struct Task_struct         *root;
    struct Task_struct         *father;
    struct Task_struct         *brother;
    struct Task_struct         *lastson;
    struct Task_struct         *firstson;

    struct Task_struct         *next;           /*Ӧ��������*/
}task_struct;

#endif

extern void wait(int *);
extern void signal(int *);
