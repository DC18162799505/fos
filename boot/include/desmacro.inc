;===============================================================================
;VERSION    0.1
;===============================================================================



;-------------------------------------------------------------------------------
; VALUE OF DEC TYPE AS FOLLOW:
;-------------------------------------------------------------------------------
;       DA_  : Descriptor Attribute
;       D    : DATA DEC
;       E    : CODE DEC
;       S    : SYS  DEC
;       R    : ONLY READ
;       RW   : READ AND WRITE
;       A    : ACCESSED
;       C    : CO CODE DES
;       SA   ; SELECTOR ATTRIBUTE
;       TG   ; TASK GATE
;-------------------------------------------------------------------------------
; DPL
;-------------------------------------------------------------------------------
DA_32        EQU       4000H        ;32 BITS CODE
DA_LIMIT_4K	 EQU	   8000h	    ;page size

DA_DPL0      EQU       00H          ;DPL = 0
DA_DPL1      EQU       20H          ;DPL = 1
DA_DPL2      EQU       40H          ;DPL = 2
DA_DPL3      EQU       60H          ;DPL = 3
;-------------------------------------------------------------------------------
; DATA DES
;-------------------------------------------------------------------------------
DA_D_R       EQU       90H          ;DATA DES WITH ONLY READ
DA_D_RW      EQU       92H          ;DATA DES WITH READ AND WRITE
DA_D_RWA     EQU       93H          ;DATA DES WITH READ , WRITE AND ACCESSED
DA_E_        EQU       98H          ;CODE DES
DA_E_R       EQU       9AH          ;CODE DES WITH READ
DA_E_C       EQU       9CH          ;CODE DES WITH CO CODE
DA_E_E       EQU       9EH          ;CODE DES WITH CO CODE , READ
;-------------------------------------------------------------------------------
; SYSTEM DES
;-------------------------------------------------------------------------------
DA_S_LDT        EQU       82H          ;LOCAL DESCRIPTOR
DA_S_TG         EQU       85H          ;TASK GATE
DA_S_386TSS     EQU       89H          ;STATUS OF TASK
DA_S_386CGATE   EQU       8CH          ;CALL GATE
DA_S_386IGATE   EQU       8EH          ;INTERRUPT GATE
DA_S_386TGATE   EQU       8FH          ;TRAP GATE
;-------------------------------------------------------------------------------
; SELECTOR
;-------------------------------------------------------------------------------
SA_RPL0         EQU       00H          ;RPL = 0
SA_RPL1         EQU       01H          ;RPL = 1
SA_RPL2         EQU       02H          ;RPL = 2
SA_RPL3         EQU       03H          ;PRL = 4

SA_TIL          EQU       04H          ;LOCAL
SA_TIG          EQU       00H          ;GLOBA
;-------------------------------------------------------------------------------
; PAGE
;-------------------------------------------------------------------------------
PG_P		EQU	1	; PRESENT BIT
PG_RW_R		EQU	0	; R/W READ AND EXECUTE
PG_RW_W		EQU	2	; R/W READ, EXECUTE AND WRITE
PG_US_S		EQU	0	; U/S SUPERVISOR
PG_US_U		EQU	4	; U/S USER
;-------------------------------------------------------------------------------
; MACRO
;-------------------------------------------------------------------------------
%macro   Descriptor    3               ;base:limit:attributes
         dw     %2 &  0FFFFh           ;limiteL(0-15)
         dw     %1 &  0FFFFh           ;baseL(0-15)
         db     (%1 >> 16) &  0FFh     ;baseM(16-24)
         dw     ((%2 >> 8) & 0F00h) | (%3 & 0F0FFh)
                                       ;attr1 + limiteh + attr2
         db     (%1 >> 24) & 0FFh      ;baseh(25-31)
%endmacro

%macro   Gate           4                           ; selector:offset:Dcount:Attr
	     dw	    (%2 & 0FFFFh)				        ; OFFSET1				(2 字节)
	     dw	    %1					                ; SELECTOR				(2 字节)
         dw	    (%3 & 1Fh) | ((%4 << 8) & 0FF00h)	; ATTR					(2 字节)
	     dw	    ((%2 >> 16) & 0FFFFh)			    ; OFFSET2				(2 字节)
%endmacro

%macro   TSS            0
%%Label_tss:
         DD      0                     ; back
         DD      0                     ; sp         DPL 0
         DW      0                     ; ss  
         DW      0     
         DD      0                     ; DPL1
         DD      0                     ;
         DD      0                     ; DPL2
         DD      0                     ;
         DD      0                     ; cr3
         DD      0                     ; eip
         DD      0                     ; eflags
         DD      0                     ; eax
         DD      0                     ; ecx
         DD      0                     ; edx
         DD      0                     ; ebx
         DD      0                     ; esp
         DD      0                     ; ebp
         DD      0                     ; esi
         DD      0                     ; edi
         DD      0                     ; es
         DD      0                     ; cs
         DD      0                     ; ss
         DD      0                     ; ds
         DD      0                     ; fs
         DD      0                     ; gs 
         DD      0                     ; Ldt
         DW      0                     ; debug trap
         DW      $ - %%Label_tss + 2   ; I / O bit map base
         DW      0FFh                  ; I / O bit map end      
%endmacro
;-------------------------------------------------------------------------------
