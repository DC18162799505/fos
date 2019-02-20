;===============================================================================
%include "desmacro.asm"
%include "video.asm"
%include "protect.inc"
%include "klib.asm"
;===============================================================================
extern  cmain

global _start
[SECTION .text]
[BITS 32]
_start:
    mov word ax, 0x10
    mov ds, ax
        
    lidt [IdtPtr]
    lgdt [GdtPtr]
    
    mov word ax, 0x10
    mov ds, ax
    ;内核堆栈 
    mov ss, ax
    mov dword esp, 90000h
    ;视频选择子 
    mov word ax, 0x18
    mov gs, ax    

    
    ;检查A20是否开启 
    xor eax,eax
    mov [0x100000],eax
    cmp eax,[0x00000]
    je  $
    
    ;检查80x87协处理器 
    call Check_x87
    
    ;启用分页机制
    call Setup_paging              

    push dword 0
    push dword 0
    call cmain
End_code:
         
	mov	ah, 0Fh				; 0000: 黑底    1111: 白字
	mov	al, 'L'
	mov	[gs:((80 * 0 + 39) * 2)], ax	; 屏幕第 0 行, 第 39 列。
	
	jmp	$		;一般情况下不会到这里，如果到这里，就说明程序错误 
;===============================================================================
;开启分页机制 
;-------------------------------------------------------------------------------
Setup_paging:                ;页表在内存中是连续的 
    mov word ax,Kerneld_sel
    mov es,ax
    
    mov dword eax,[0x90000]    
    shr eax,22
    mov ecx,eax
    mov dword edi,PageDirBase
    xor eax,eax
    mov dword eax,PageTabBase | PG_P | PG_US_U | PG_RW_W
    
.loop_dir:
    stosd
    add eax, 4096
    loop .loop_dir
    
    mov dword eax,[0x90000]
    shr eax,12
    mov ecx,eax
    mov dword edi,PageTabBase
    xor eax,eax
    mov dword eax,PG_P | PG_US_U | PG_RW_W
.loop_tab:
    stosd
    add eax, 4096
    loop .loop_tab
    
    ChangePaging PageDirBase
    EnPaging
    
    ret
;===============================================================================
;80x87协处理器的设置 
;-------------------------------------------------------------------------------
Check_x87:
    mov  eax,01h
    cpuid
    and  edx,01h
    cmp  edx,01h
    je   Label_p
    mov  eax,cr0
    and  eax,Coprocessor_np1
    or   eax,Coprocessor_np2
    mov  cr0,eax
    ret
    
Label_p:
    mov  eax,cr0
    and  eax,Coprocessor_p1
    or   eax,Coprocessor_p2
    mov  cr0,eax 
    ret
;===============================================================================
;GDT DEC
;-------------------------------------------------------------------------------
[SECTION .gdt]
Label_gdt:
Label_dump:     Descriptor      0,0,0
Label_Kernelc:  Descriptor      0,0FFFFFh,DA_E_ | DA_32 | DA_LIMIT_4K
Label_Kerneld:  Descriptor      0,0FFFFFh,DA_D_RW | DA_32 | DA_LIMIT_4K
Label_Video:    Descriptor      VideoBuf32,0FFFFh,DA_D_RW | DA_DPL3
Label_Kernels:  Descriptor      0,0,0
%rep     251
         Descriptor  0,0,0
%endrep

Gdtlen   equ         $ - Label_gdt
GdtPtr   dw          Gdtlen - 1
         dd          Label_gdt

Kernelc_sel     equ             Label_Kernelc - Label_gdt
Kerneld_sel     equ             Label_Kerneld - Label_gdt
Video_sel       equ             Label_Video - Label_gdt + SA_RPL3
;-------------------------------------------------------------------------------
;IDT DEC
;-------------------------------------------------------------------------------
[SECTION .idt]
Label_idt:
%rep     256
         Gate  0,0,0,0
%endrep

Idtlen   equ         $ - Label_idt
IdtPtr   dw          Idtlen - 1
         dd          Label_idt
;===============================================================================
