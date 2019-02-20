#include "type.h"
#include "protect.h"
#include  "regctl.h"

unsigned char get_fs_byte(const char * addr)
{
    unsigned register char _v;

    __asm__ ("movb %%fs:%1,%0":"=r" (_v):"m" (*addr));
    return _v;
}

unsigned short get_fs_word(const unsigned short *addr)
{
    unsigned short _v;

    __asm__ ("movw %%fs:%1,%0":"=r" (_v):"m" (*addr));
    return _v;
}

unsigned long get_fs_long(const unsigned long *addr)
{
    unsigned long _v;

    __asm__ ("movl %%fs:%1,%0":"=r" (_v):"m" (*addr)); 
    return _v;
}

void put_fs_byte(char val,char *addr)
{
    __asm__ ("movb %0,%%fs:%1"::"r" (val),"m" (*addr));
}

void put_fs_word(short val,short * addr)
{
    __asm__ ("movw %0,%%fs:%1"::"r" (val),"m" (*addr));
}

void put_fs_long(unsigned long val,unsigned long * addr)
{
    __asm__ ("movl %0,%%fs:%1"::"r" (val),"m" (*addr));
}

unsigned long get_fs() 
{
    unsigned short _v;
    __asm__("mov %%fs,%%ax":"=a" (_v):);
    return _v;
}

unsigned long get_ds() 
{
    unsigned short _v;
    __asm__("mov %%ds,%%ax":"=a" (_v):);
    return _v;
}

void set_fs(unsigned long val)
{
    __asm__("mov %0,%%fs"::"a" ((unsigned short) val));
}

unsigned long get_cr2_long()
{
    unsigned long _v;

    __asm__ ("movl %%cr2,%0":"=r" (_v):);
    return _v;
}

unsigned long get_cr3_long()
{
    unsigned long _v;

    __asm__ ("movl %%cr3,%0":"=r" (_v):);
    return _v;
}

unsigned long put_cr3_long(const unsigned long value)
{
    __asm__("movl %%eax,%%cr3"::"a" (value)); 
}
