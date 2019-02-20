#include  "type.h"
#include  "protect.h"
#include  "fos\sys.h"

intr_handler sys_call_table[] = {sys_write,sys_fork,sys_execve};

int init_sys_call()
{
    set_idt_desc(INT_VECTOR_SYS_CALL,DA_S_386TGATE,sys_call,Privilege_user);
    return 0;
}
