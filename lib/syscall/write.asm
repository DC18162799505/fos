extern  current

global  write

[SECTION .text]
[BITS 32]
write:                                  ;void write(char *buf,int len);
       mov   eax,0
       mov   edx,[current]
       mov   ebx,[esp + 4]
       mov   ecx,[esp + 8]
       int   0x80
       ret
