#include     "type.h"
#include     "protect.h"
#include     "regctl.h"
#include     "fos\keyboard.h"
#include     "fos\console.h"
#include     "fos\tty.h"
#include     "sys\proc.h"
#include     "sys\kernel.h"
#include     "fos\memory.h"
#include     "sys\system.h"
#include     "string.h"

int getid()
{
    return current->pid;
}

char* getpname()
{
    return current->name;
}

void task_init()
{
    init_task.counts = 1;
    init_task.stat = TASK_RUNNING;
    init_task.priority = Priority_1;
    init_task.pid  = 0;
    init_task.name[0] = 'r';
    init_task.name[1] = 'o';
    init_task.name[2] = 'o';
    init_task.name[3] = 't';
    
    /*基址是0,段限4G,32位代码段，4k的页面，特权级3*/
    set_descriptor(&init_task.ldts[0],0,0xFFFFF,(DA_32 | DA_LIMIT_4K | DA_E_ | DA_DPL3));
    set_descriptor(&init_task.ldts[1],0,0xFFFFF,(DA_32 | DA_LIMIT_4K | DA_D_RW | DA_DPL3));
    /*基址是1G,段限3G,32位代码段，4k的页面，特权级3*/
    set_descriptor(&init_task.ldts[2],0x40000000,0xBFFFF,(DA_32 | DA_LIMIT_4K | DA_E_ | DA_DPL3));
    set_descriptor(&init_task.ldts[3],0x40000000,0xBFFFF,(DA_32 | DA_LIMIT_4K | DA_D_RW | DA_DPL3));
    init_task.tty_sn = 0;
    
    /*整个内存地址*/
    init_task.data_start = 0x40000000;
    init_task.data_end = 0x40000000;
    
    init_task.file_fd = -1;
    
    init_task.root = NULL;
    init_task.father = NULL;
    init_task.brother = NULL;
    init_task.firstson = NULL;
    init_task.lastson = NULL;
    
    /*初始化进程0的状态*/    
    init_task.tss.ldt = LDT(0);
    init_task.tss.cr3 = PageDirBase | PG_P | PG_US_U | PG_RW_W;
    init_task.tss.cs  = 0x7;
    init_task.tss.ds  = 0xf;
    init_task.tss.ss0 = Selector_kernel_ds;
    init_task.tss.esp0 = Kernel_SS;
    put_page(get_cr3_long(),pg2add8(get_free_app()),Kernel_SS - 1);
    init_task.tss.flags = 0x00003212;
    init_task.tss.esp = 0xFFFFFFFC;
}

/* 将初始化程序写装入进程0 */
int init_kernel()
{
    int i;
    
    Tasks[0] = &init_task;
    current = &init_task;
    task_init();

    set_descriptor(&Gdt[TSS_INDEX(0)],(int32)&(init_task.tss),sizeof(init_task.tss) - 1,DA_S_386TSS | DA_DPL3);
    ltr(TSS(0));
    /*加载init_task的局部描述符*/ 
    set_descriptor(&Gdt[LDT_INDEX(0)],(int32)(init_task.ldts),LDT_SIZE * 8,DA_S_LDT);
    lldt(LDT(0));
    
    for(i = 1;i < NR_TASKS;i ++)
          Tasks[i] = NULL;

    return 0;
}
