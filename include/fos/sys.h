/*------------------------------------------------------------------------------
  系统调用 
------------------------------------------------------------------------------*/

#ifndef        _SYS_H_
#define        _SYS_H_

#define        INT_VECTOR_SYS_CALL      0x80

#define        __NR_write               0x0              /*int write()   */
#define        __NR_fork                0x1              /*int fork()    */
#define        __NR_execve              0x2              /*int execve()  */

#define _syscall0(type,name) \
type name(void) \
{ \
   long __res; \
   __asm__ volatile ("int $0x80" \
       : "=a" (__res) \
       : "0" (__NR_##name)); \
   if (__res >= 0) \
       return (type) __res; \
   return -1; \
}

/*ebx*/
#define _syscall1(type,name,atype,a) \
type name(atype a) \
{ \
   long __res; \
   __asm__ volatile ("int $0x80" \
       : "=a" (__res) \
       : "0" (__NR_##name),"b" ((long)(a))); \
   if (__res >= 0) \
       return (type) __res; \
   return -1; \
}

/*ebx,ecx*/
#define _syscall2(type,name,atype,a,btype,b) \
type name(atype a,btype b) \
{ \
   long __res; \
   __asm__ volatile ("int $0x80" \
       : "=a" (__res) \
       : "0" (__NR_##name),"b" ((long)(a)),"c" ((long)(b))); \
   if (__res >= 0) \
       return (type) __res; \
   return -1; \
}

/*ebx,ecx,edx*/
#define _syscall3(type,name,atype,a,btype,b,ctype,c) \
type name(atype a,btype b,ctype c) \
{ \
   long __res; \
   __asm__ volatile ("int $0x80" \
       : "=a" (__res) \
       : "0" (__NR_##name),"b" ((long)(a)),"c" ((long)(b)),"d" ((long)(c))); \
   if (__res>=0) \
       return (type) __res; \
   return -1; \
}

typedef        int  (*intr_handler)    ();

#endif

extern  int    sys_write();
/*---------------------------------------------------------------------------
sys_fork.c
---------------------------------------------------------------------------*/
extern  int    find_empty_process();
extern  int    sys_fork();
extern  int    sys_execve();

extern  intr_handler    sys_call_table[];


void   sys_call();                                         /*系统调用处理函数*/

extern  int    init_sys_call();
