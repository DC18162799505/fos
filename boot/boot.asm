;===============================================================================
%include     "real.inc"
%include     "fat12.asm"
%include     "string.asm"
%include     "video.asm"
;===============================================================================
     org    07c00h
;===============================================================================
;  fat12
;-------------------------------------------------------------------------------
      jmp     short Start
      nop
	BS_OEMName	    DB 'FZU     '	  ; OEM String, ���� 8 ���ֽ�
	BPB_BytsPerSec	DW 512		      ; ÿ�����ֽ���
	BPB_SecPerClus	DB 1		      ; ÿ�ض�������
	BPB_RsvdSecCnt	DW 1		      ; Boot ��¼ռ�ö�������
	BPB_NumFATs	    DB 2		      ; ���ж��� FAT ��
	BPB_RootEntCnt	DW 224		      ; ��Ŀ¼�ļ������ֵ
	BPB_TotSec16	DW 2880		      ; �߼���������
	BPB_Media	    DB 0xF0		      ; ý��������
	BPB_FATSz16	    DW 9		      ; ÿFAT������
	BPB_SecPerTrk	DW 18		      ; ÿ�ŵ�������
	BPB_NumHeads	DW 2		      ; ��ͷ��(����)
	BPB_HiddSec	    DD 0		      ; ����������
	BPB_TotSec32	DD 0		      ; ��� wTotalSectorCount �� 0 �����ֵ��¼������
	BS_DrvNum	    DB 0		      ; �ж� 13 ����������
	BS_Reserved1	DB 0		      ; δʹ��
	BS_BootSig	    DB 29h		      ; ��չ������� (29h)
	BS_VolID	    DD 0		      ; �����к�
	BS_VolLab	    DB 'FOS0.00.00 '  ; ���, ���� 11 ���ֽ�
	BS_FileSysType	DB 'FAT12   '     ; �ļ�ϵͳ����, ���� 8���ֽ�
;===============================================================================
Start:
    mov    ax,cs
    mov    ds,ax
    mov    ss,ax
    mov    sp,07c00h
      
    ;������λ 
    xor    ah,ah
    xor    dl,dl
    int    13h
        
    ;һ���Զ����Ŀ¼      
    mov      word ax,TempBase
    mov      es,ax
    mov      word bx,TempOffset    
    mov      word ax,Fat12_offset_root
    mov      byte cl,RootDirSec
    call     ReadSector
    
    ;һ���Զ���fatĿ¼��9������ 
    mov      bx,TempOffset1   
    mov      word ax,Fat12_offset_fat1
    mov      byte cl,9
    call     ReadSector       
        
    cld
            
    ;Ѱ�Ҳ�����"Loader.bin"  �� "Kernel.bin" 
    mov     word [FileAddr],LoaderFileName
    mov     word [LoadfileOff],LoaderOffset
    mov     word [LoadfileBase],LoaderBase
    call    Search
    
    mov     word [FileAddr],KernelFileName
    mov     word [LoadfileOff],KernelOffset
    mov     word [LoadfileBase],KernelBase
    call    Search
        
    ;�ر�������� 
   	mov	dx, 03F2h
	mov	al, 0
	out	dx, al  
            
    jmp      LoaderBase:LoaderOffset    
;===============================================================================
LoaderFileName:         db              'LOADER  BIN'
KernelFileName:         db              'KERNEL  BIN'
FileAddr:               dw              0
LoadfileBase:           dw              0
LoadfileOff:            dw              0

Message2:               db              'Failed...$'
TempNext:               dw              0
TempOff:                dw              0    
;===============================================================================
Search:
    call    Searchfile       
    cmp     cx,0
    jz      Label_fail
    
    mov     word ax,[es:Fat12_dir_fstclus]
    mov     [TempNext],ax 
    jmp     Label_suc  
Label_fail:
    Position 2,0
    mov      cx,Message2
    call     DisplayString   

    jmp     $
 
Label_suc:    
    ;ͨ��fatĿ¼�����ļ�
    call     Loadfile        
    ret
;-------------------------------------------------------------------------------
Searchfile:
    mov     cx,[BPB_RootEntCnt]
    mov     word ax,TempBase
    mov     es,ax
Label_loop:
    xor     di,di
    push    cx
    mov     cx,11
    mov     si,[FileAddr]
    .loop:
            lodsb
            cmp     byte al,[es:di]
            jnz     Label_dif     
            inc     di   
            loop    .loop
    pop     cx
    jmp     Label_break
  Label_dif:
    mov     ax,es
    add     ax,2
    mov     es,ax
    pop     cx
    loop    Label_loop
Label_break:     
    ret
;-------------------------------------------------------------------------------
Loadfile:
    mov      word ax,[LoadfileOff]
    mov      [TempOff],ax    
    mov      word ax,[TempNext]
Label_jcond:
    mov      [TempNext],ax
    mov      word ax,[LoadfileBase]
    mov      es,ax
    mov      word bx,[TempOff]
    mov      ax,bx
    add      ax,512
    mov      [TempOff],ax
    mov      word ax,[TempNext]
    add      ax,31
    mov      byte cl,1
    call     ReadSector
    mov      word ax,[TempNext]             
    mov      si,ax
    mov      cx,si
    and      word cx,0001h
    shr      ax,1
    mov      word bx,3
    mul      bx
    mov      si,ax
    mov      ax,TempBase
    mov      es,ax
    add      si,TempOffset1
    cmp      word cx,01h
    je       Label_odd
Label_even:  
    xor      ax,ax
    mov      byte al,[es:si]
    inc      si
    mov      byte ah,[es:si]
    and      word ax,0FFFh
    jmp      Label_next
Label_odd:
    inc      si   
    xor      ax,ax
    mov      byte al,[es:si]
    inc      si
    mov      byte ah,[es:si]
    shr      ax,4
Label_next:   
    mov      si,ax
    cmp      si,0FF6h
    jle      Label_jcond
    
    ret
;-------------------------------------------------------------------------------    
ReadSector:
    jmp     .Label_start
    .reg1   dw      0
    .reg2   db      0
.Label_start:
    mov     [.reg1],ax
    mov     [.reg2],cl
    Sector_cal  [.reg1],[BPB_SecPerTrk]
    Sector_read [.reg2],[BS_DrvNum]           
    ret
;-------------------------------------------------------------------------------
DisplayString:
    jmp     .Label_start
    .reg3   dd       0
.Label_start:
    mov     word [.reg3],cx
    mov     ax,VideoBuf16
    mov     gs,ax
    Displaystr    [.reg3]    
    ret
times       510 - ($ - $$)     db        0
dw          0xaa55
