#ifndef      _SYSTEM_H_
#define      _SYSTEM_H_

/*先推入堆栈，然后是标志寄存器，然后是返回地址*/
/* 需要修改*/
#define TSS(n) (((n + 1) << 2) << 3)
#define LDT(n) (((((n + 1) << 2) + 1) << 3) + 3)
#define TSS_INDEX(n) ((n + 1) << 2)
#define LDT_INDEX(n) (((n + 1) << 2) + 1)

#define move_to_user_mode() \
__asm__ ("movl %%esp,%%eax\n\t" \
    "pushl $0xf\n\t" \
    "pushl $0xFFFFFFFC\n\t" \
    "pushl $0x00003212\n\t" \
    "pushl $0x07\n\t" \
    "pushl $1f\n\t" \
    "iret\n" \
    "1:\tmovl $0xf,%%eax\n\t" \
    "movw %%ax,%%ds\n\t" \
    "movw %%ax,%%es\n\t" \
    "movw %%ax,%%fs\n\t" \
    :::"ax")

#define switch_to(n) {\
struct {long a,b;} __tmp; \
__asm__("cmpl %%ecx,current\n\t" \
    "je 1f\n\t" \
    "movw %%dx,%1\n\t" \
    "xchgl %%ecx,current\n\t" \
    "ljmp *%0\n\t" \
    "1:" \
    ::"m" (*&__tmp.a),"m" (*&__tmp.b), \
    "d" (TSS(n)),"c" ((long) Tasks[n])); \
}

#endif
