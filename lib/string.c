/*------------------------------------------------------------------------------
   ×Ö·û´®´¦Àí 
------------------------------------------------------------------------------*/
#include  "type.h"
#include  "string.h"
#include  "stdarg.h"
#include  "syscall.h"

int    print_int(int32 val,char* orient)
{
       int i,tem;
       char  str[20],*out = orient;
       
       if(val == 0)
       {
       	   *out++ = '0';
       	   return 1;
       }
       for(i = 0;val;i ++,val /= 10)
            str[i] = val % 10 + '0';
       tem = i;
       for(i--;i >= 0;i--)
             *out++ = str[i];
       return tem;
}
void   printc(char *fmt,...)
{
       va_list ap;
       char    buffer[256];
       char    *p,*sval,*out = buffer;
       int     ival;
       
       va_start(ap,fmt);
       for(p = fmt;*p;p++)
       {
             if(*p != '%')
             {
                   *out++ = *p;
                   continue;
             }
             switch(*++p)
             {
             case 'd':
                  ival = va_arg(ap,int);
                  out += print_int(ival,out);
                  break;
             case 's':
                  for(sval = va_arg(ap,char *);*sval;sval ++)
                        *out++ = *sval;
                  break;
             default:
                  *out++ = *p;
                  break;
             }
       }
       va_end(ap);
       write(buffer,out - buffer);
}

void  printk(char *fmt,...)
{
       va_list ap;
       char    buffer[256];
       char    *p,*sval,*out = buffer;
       int     i,ival,len;
       
       va_start(ap,fmt);
       for(p = fmt;*p;p++)
       {
             if(*p != '%')
             {
                   *out++ = *p;
                   continue;
             }
             switch(*++p)
             {
             case 'd':
                  ival = va_arg(ap,int);
                  out += print_int(ival,out);
                  break;
             case 's':
                  for(sval = va_arg(ap,char *);*sval;sval ++)
                        *out++ = *sval;
                  break;
             default:
                  *out++ = *p;
                  break;
             }
       }
       va_end(ap);
       len = out - buffer;
       if(dispos > 3840)
       	    dispos = 0;
       for(i = 0;i < len;i ++)
       {
       	    switch(buffer[i])
       	    {
       	    	   case '\n':
       	    	       dispos = (dispos / 80 + 1) * 80;
       	    	       break;
       	    	   default:
       	    	   	   v_array[dispos * 2] = buffer[i];
       	    	   	   v_array[dispos * 2 + 1] = 0x0F;
       	    	   	   dispos ++;
       	    	   	   break;
       	    }
       } 	    
}

inline char * strcpy(char * dest,const char *src)
{
__asm__("cld\n"
    "1:\tlodsb\n\t"
    "stosb\n\t"
    "testb %%al,%%al\n\t"
    "jne 1b"
    ::"S" (src),"D" (dest));
return dest;
}

inline char * strncpy(char * dest,const char *src,int count)
{
__asm__("cld\n"
    "1:\tdecl %2\n\t"
    "js 2f\n\t"
    "lodsb\n\t"
    "stosb\n\t"
    "testb %%al,%%al\n\t"
    "jne 1b\n\t"
    "rep\n\t"
    "stosb\n"
    "2:"
    ::"S" (src),"D" (dest),"c" (count));
return dest;
}

inline char * strcat(char * dest,const char * src)
{
__asm__("cld\n\t"
    "repne\n\t"
    "scasb\n\t"
    "decl %1\n"
    "1:\tlodsb\n\t"
    "stosb\n\t"
    "testb %%al,%%al\n\t"
    "jne 1b"
    ::"S" (src),"D" (dest),"a" (0),"c" (0xffffffff));
return dest;
}

inline char * strncat(char * dest,const char * src,int count)
{
__asm__("cld\n\t"
    "repne\n\t"
    "scasb\n\t"
    "decl %1\n\t"
    "movl %4,%3\n"
    "1:\tdecl %3\n\t"
    "js 2f\n\t"
    "lodsb\n\t"
    "stosb\n\t"
    "testb %%al,%%al\n\t"
    "jne 1b\n"
    "2:\txorl %2,%2\n\t"
    "stosb"
    ::"S" (src),"D" (dest),"a" (0),"c" (0xffffffff),"g" (count)
    );
return dest;
}

inline int strcmp(const char * cs,const char * ct)
{
register int __res ;
__asm__("cld\n"
    "1:\tlodsb\n\t"
    "scasb\n\t"
    "jne 2f\n\t"
    "testb %%al,%%al\n\t"
    "jne 1b\n\t"
    "xorl %%eax,%%eax\n\t"
    "jmp 3f\n"
    "2:\tmovl $1,%%eax\n\t"
    "jl 3f\n\t"
    "negl %%eax\n"
    "3:"
    :"=a" (__res):"D" (cs),"S" (ct));
return __res;
}

inline int strncmp(const char * cs,const char * ct,int count)
{
register int __res ;
__asm__("cld\n"
    "1:\tdecl %3\n\t"
    "js 2f\n\t"
    "lodsb\n\t"
    "scasb\n\t"
    "jne 3f\n\t"
    "testb %%al,%%al\n\t"
    "jne 1b\n"
    "2:\txorl %%eax,%%eax\n\t"
    "jmp 4f\n"
    "3:\tmovl $1,%%eax\n\t"
    "jl 4f\n\t"
    "negl %%eax\n"
    "4:"
    :"=a" (__res):"D" (cs),"S" (ct),"c" (count));
return __res;
}

inline char * strchr(const char * s,char c)
{
register char * __res ;
__asm__("cld\n\t"
    "movb %%al,%%ah\n"
    "1:\tlodsb\n\t"
    "cmpb %%ah,%%al\n\t"
    "je 2f\n\t"
    "testb %%al,%%al\n\t"
    "jne 1b\n\t"
    "movl $1,%1\n"
    "2:\tmovl %1,%0\n\t"
    "decl %0"
    :"=a" (__res):"S" (s),"0" (c));
return __res;
}

inline char * strrchr(const char * s,char c)
{
register char * __res; 
__asm__("cld\n\t"
    "movb %%al,%%ah\n"
    "1:\tlodsb\n\t"
    "cmpb %%ah,%%al\n\t"
    "jne 2f\n\t"
    "movl %%esi,%0\n\t"
    "decl %0\n"
    "2:\ttestb %%al,%%al\n\t"
    "jne 1b"
    :"=d" (__res):"0" (0),"S" (s),"a" (c));
return __res;
}

inline int strspn(const char * cs, const char * ct)
{
register char * __res;
__asm__("cld\n\t"
    "movl %4,%%edi\n\t"
    "repne\n\t"
    "scasb\n\t"
    "notl %%ecx\n\t"
    "decl %%ecx\n\t"
    "movl %%ecx,%%edx\n"
    "1:\tlodsb\n\t"
    "testb %%al,%%al\n\t"
    "je 2f\n\t"
    "movl %4,%%edi\n\t"
    "movl %%edx,%%ecx\n\t"
    "repne\n\t"
    "scasb\n\t"
    "je 1b\n"
    "2:\tdecl %0"
    :"=S" (__res):"a" (0),"c" (0xffffffff),"0" (cs),"g" (ct)
    );
return __res-cs;
}

inline int strcspn(const char * cs, const char * ct)
{
register char * __res;
__asm__("cld\n\t"
    "movl %4,%%edi\n\t"
    "repne\n\t"
    "scasb\n\t"
    "notl %%ecx\n\t"
    "decl %%ecx\n\t"
    "movl %%ecx,%%edx\n"
    "1:\tlodsb\n\t"
    "testb %%al,%%al\n\t"
    "je 2f\n\t"
    "movl %4,%%edi\n\t"
    "movl %%edx,%%ecx\n\t"
    "repne\n\t"
    "scasb\n\t"
    "jne 1b\n"
    "2:\tdecl %0"
    :"=S" (__res):"a" (0),"c" (0xffffffff),"0" (cs),"g" (ct)
    );
return __res-cs;
}

inline char * strpbrk(const char * cs,const char * ct)
{
register char * __res ;
__asm__("cld\n\t"
    "movl %4,%%edi\n\t"
    "repne\n\t"
    "scasb\n\t"
    "notl %%ecx\n\t"
    "decl %%ecx\n\t"
    "movl %%ecx,%%edx\n"
    "1:\tlodsb\n\t"
    "testb %%al,%%al\n\t"
    "je 2f\n\t"
    "movl %4,%%edi\n\t"
    "movl %%edx,%%ecx\n\t"
    "repne\n\t"
    "scasb\n\t"
    "jne 1b\n\t"
    "decl %0\n\t"
    "jmp 3f\n"
    "2:\txorl %0,%0\n"
    "3:"
    :"=S" (__res):"a" (0),"c" (0xffffffff),"0" (cs),"g" (ct)
    );
return __res;
}

inline char * strstr(const char * cs,const char * ct)
{
register char * __res ;
__asm__("cld\n\t" \
    "movl %4,%%edi\n\t"
    "repne\n\t"
    "scasb\n\t"
    "notl %%ecx\n\t"
    "decl %%ecx\n\t"    /* NOTE! This also sets Z if searchstring='' */
    "movl %%ecx,%%edx\n"
    "1:\tmovl %4,%%edi\n\t"
    "movl %%esi,%%eax\n\t"
    "movl %%edx,%%ecx\n\t"
    "repe\n\t"
    "cmpsb\n\t"
    "je 2f\n\t"     /* also works for empty string, see above */
    "xchgl %%eax,%%esi\n\t"
    "incl %%esi\n\t"
    "cmpb $0,-1(%%eax)\n\t"
    "jne 1b\n\t"
    "xorl %%eax,%%eax\n\t"
    "2:"
    :"=a" (__res):"0" (0),"c" (0xffffffff),"S" (cs),"g" (ct)
    );
return __res;
}

inline int strlen(const char * s)
{
register int __res ;
__asm__("cld\n\t"
    "repne\n\t"
    "scasb\n\t"
    "notl %0\n\t"
    "decl %0"
    :"=c" (__res):"D" (s),"a" (0),"0" (0xffffffff));
return __res;
}

inline void * memcpy(void * dest,const void * src, int n)
{
__asm__("cld\n\t"
    "rep\n\t"
    "movsb"
    ::"c" (n),"S" (src),"D" (dest)
    );
return dest;
}

inline void * memmove(void * dest,const void * src, int n)
{
if (dest<src)
__asm__("cld\n\t"
    "rep\n\t"
    "movsb"
    ::"c" (n),"S" (src),"D" (dest)
    );
else
__asm__("std\n\t"
    "rep\n\t"
    "movsb"
    ::"c" (n),"S" (src+n-1),"D" (dest+n-1)
    );
return dest;
}

inline int memcmp(const void * cs,const void * ct,int count)
{
register int __res ;
__asm__("cld\n\t"
    "repe\n\t"
    "cmpsb\n\t"
    "je 1f\n\t"
    "movl $1,%%eax\n\t"
    "jl 1f\n\t"
    "negl %%eax\n"
    "1:"
    :"=a" (__res):"0" (0),"D" (cs),"S" (ct),"c" (count)
    );
return __res;
}

inline void * memchr(const void * cs,char c,int count)
{
register void * __res ;
if (!count)
    return NULL;
__asm__("cld\n\t"
    "repne\n\t"
    "scasb\n\t"
    "je 1f\n\t"
    "movl $1,%0\n"
    "1:\tdecl %0"
    :"=D" (__res):"a" (c),"D" (cs),"c" (count)
    );
return __res;
}

inline void * memset(void * s,char c,int count)
{
__asm__("cld\n\t"
    "rep\n\t"
    "stosb"
    ::"a" (c),"D" (s),"c" (count)
    );
return s;
}
