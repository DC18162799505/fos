extern  current

global  execve

[SECTION .text]
[BITS 32]
execve:                                  ;void write(char *buf,int len);
       mov   eax,2
       mov   ebx,[esp + 4]
       mov   ecx,[esp + 8]
       int   0x80
       ret
