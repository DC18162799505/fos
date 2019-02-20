;===============================================================================
;VERSION    0.1
;===============================================================================

;===============================================================================
%macro  EnableA20 0
        in       al,92h
        or       al,00000010b
        out      92h,al
%endmacro

%macro  DisableA20 0
        in       al,92h
        and      al,11111101b
        out      92h,al
%endmacro
;===============================================================================
%macro  EnProtectMode 0
        mov      eax,cr0
        or       eax,1
        mov      cr0,eax       
%endmacro

%macro  DisProtectMode 0
        mov      eax,cr0
        and      al,11111110b
        mov      cr0,eax
%endmacro
;===============================================================================
%macro  ChangePaging 1
        mov      eax, %1
        mov      cr3, eax
%endmacro

%macro  EnPaging   0
	    mov	     eax, cr0
	    or	     eax, 80000000h
	    mov	     cr0, eax
%endmacro
;===============================================================================
%macro  dos_return 0
        mov   ax,4c00h
        int   21h
%endmacro
;===============================================================================
%macro  DelayIO  0
        jmp     %%loop
%%loop:
        nop
        nop
        nop
        nop
%endmacro
;===============================================================================
%macro  Icw_8259A    6                 ;Addr1,Addr2,icw1,icw2,icw3,icw4
        push    ax
        push    dx
        
        mov     word dx,%1
        mov     byte al,%3
        out     dx,al
        DelayIO
        
        mov     word dx,%2
        mov     byte al,%4
        out     dx,al
        DelayIO
        
        mov     byte al,%5
        out     dx,al
        DelayIO
        
        mov     byte al,%6
        out     dx,al
        DelayIO
        
        pop     dx
        pop     ax
%endmacro
;-------------------------------------------------------------------------------
%macro  Ocw_8259A     2              ;Addr,ocw
        push    dx
        push    ax
        
        mov     word dx,%1
        mov     byte al,%2
        out     dx,al
        DelayIO
        
        pop     ax
        pop     dx 
%endmacro
;===============================================================================
