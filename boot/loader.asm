;===============================================================================
%include      "real.inc"   
%include      "string.asm"
%include      "video.asm"
%include      "bios.asm"   
%include      "desmacro.asm"
%include      "klib.asm"
;===============================================================================
      jmp     Start
;===============================================================================
[SECTION .data]              
StackBase     equ         9000h

Message1:     db          'Memory Size = $'
Temval:       dd          0
;-------------------------------------------------------------------------------
[SECTION .gdt]
Label_gdt:    Descriptor  0,0,0
Label_code:   Descriptor  0,0FFFFFh,DA_E_ | DA_32 | DA_LIMIT_4K
Label_data:   Descriptor  0,0FFFFFh,DA_D_RW | DA_32 | DA_LIMIT_4K
Label_video:  Descriptor  VideoBuf32,0FFFFh,DA_D_RW | DA_DPL3

Gdtlen        equ         $ - Label_gdt
GdtPtr:       dw          Gdtlen - 1
              dd          LoaderBase32 + Label_gdt
              
Code_sel      equ         Label_code - Label_gdt
Data_sel      equ         Label_data - Label_gdt
Video_sel     equ         Label_video - Label_gdt + SA_RPL3
;===============================================================================        
Start:
      mov     ax,cs
      mov     ds,ax
      mov     ax,StackBase
      mov     ss,ax
      mov     sp,ax
      
      mov     ax,InfoBase
      mov     fs,ax

      ;获取并存储内存大小 
      Position 4,0
      mov     cx,Message1
      call    DisplayString      
      MemorySize
      shl     eax,10
      add     eax,100000h
      call    DisplayInt
      mov     dword [fs:0],eax
      
      ;将kernel复制到0:0 
      xor     eax,eax
      mov     es,ax
      mov     ax,KernelBase
      mov     ds,ax
      mov     ecx,60000h
      ;call    Strcpy
      Memcpy  0,0,60000h
            
      mov     ax,cs
      mov     ds,ax
      lgdt    [GdtPtr]
      
      call    Init_8259A
      
      cli
      
      EnableA20
      
      EnProtectMode      
       
      jmp     dword Code_sel:0         
;===============================================================================      
DisplayString:
      jmp     .Label_start
      .reg   dd       0
.Label_start:
      mov     word [.reg],cx
      mov     ax,VideoBuf16
      mov     gs,ax
      Displaystr    [.reg]    
      ret      
;-------------------------------------------------------------------------------
DisplayInt:
      jmp     .Label_start
      .reg    dd       0
.Label_start
      mov     dword [.reg],eax
      Displayint    [.reg],0ch
      ret
;-------------------------------------------------------------------------------
;Strcpy:
;      jmp     .Label_start
;      .reg    dd       0
;.Label_start
;      mov     dword [.reg],ecx
;      Memcpy  0,0,[.reg]
;      ret
;-------------------------------------------------------------------------------
Init_8259A:
      Icw_8259A   0x20,0x21,0x11,0x20,0x04,0x01
      Icw_8259A   0xA0,0xA1,0x11,0x28,0x02,0x01
      
      Ocw_8259A   0x21,0xFF
      Ocw_8259A   0xA1,0xFF    
      ret
;-------------------------------------------------------------------------------
