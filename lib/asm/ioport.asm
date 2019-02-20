;===============================================================================
;VERSION    0.1
;===============================================================================

[SECTION .text]
[BITS 32]
global        inb
global        outb
global        inw
global        outw

inb:        ;void    inb(int16);
     push    ebp
     mov     ebp,esp
     push    dx
     
     mov     word dx,[ebp + 8]    
     in      al,dx
     
     pop     dx
     mov     esp,ebp
     pop     ebp
     ret

outb:       ;void    outb(int16,int8);
     push    ebp
     mov     ebp,esp
     push    ax
     push    dx
     
     mov     word dx,[ebp + 8]    
     mov     byte al,[ebp + 12]
     out     dx,al
     
     pop     dx
     pop     ax
     mov     esp,ebp
     pop     ebp
     ret

inw:        ;void    inw(int16);
     push    ebp
     mov     ebp,esp
     push    dx
     
     mov     word dx,[ebp + 8]    
     in      ax,dx
     
     pop     dx
     mov     esp,ebp
     pop     ebp
     ret

outw:       ;void    outw(int16,int16);
     push    ebp
     mov     ebp,esp
     push    ax
     push    dx
     
     mov     word dx,[ebp + 8]    
     mov     word ax,[ebp + 12]
     out     dx,ax
     
     pop     dx
     pop     ax
     mov     esp,ebp
     pop     ebp
     ret


