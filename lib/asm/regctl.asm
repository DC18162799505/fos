;===============================================================================
;VERSION    0.1
;===============================================================================


[SECTION .text]
[BITS 32]
global   Sgdt_call
global   Sidt_call
global   Change_eflages              ;Change_eflages();

Change_eflages:
     push    ebp
     mov     ebp,esp
     push    ebx
     
     pushf
     pop     ebx
     or      dword ebx,0x3002
     push    ebx
     popf
     
     pop     ebx
     mov     esp,ebp
     pop     ebp
     ret
     
Sgdt_call:
     push    ebp
     mov     ebp,esp   
     push    ebx
     
     mov     dword ebx,[ebp + 8]
     sgdt    [ebx]
     
     pop     ebx
     mov     esp,ebp
     pop     ebp   
     ret
      
Sidt_call:
     push    ebp
     mov     ebp,esp   
     push    ebx
     
     mov     dword ebx,[ebp + 8]
     sidt    [ebx]
     
     pop     ebx     
     mov     esp,ebp
     pop     ebp  
     ret
