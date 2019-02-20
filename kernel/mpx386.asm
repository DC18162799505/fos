%include   "sys\intr.inc"

extern     current
extern     irq_table
extern     sys_call_table

extern     super_handler
extern     super_irq

global     Timer_intr
global     Kerboard_intr
global     Serial2_intr
global     Serial1_intr
global     Lpt2_intr
global     Floppy_intr
global     Lpt1_intr

global     Real_intr
global     Mouse_intr
global     Fpu_intr
global     Atwin_intr

global	   divide_error
global	   single_step_exception
global	   nmi
global	   breakpoint_exception
global	   overflow
global	   bounds_check
global	   inval_opcode
global	   copr_not_available
global	   double_fault
global	   copr_seg_overrun
global	   inval_tss
global	   segment_not_present
global	   stack_exception
global	   general_protection
global	   page_fault
global	   copr_error
                       
global     sys_call

global     Disable_irq
global     Enable_irq

global     call_user
global     jmp_user

[SECTION .text]
[BITS 32]
irq_intr:
     call     super_irq
     add      esp,4
     hlt

save:
	pushad		
	push	ds	
	push	es	
	push	fs	
	push	gs
	
	mov   esi,edx	
	mov	  dx, ss
	mov	  ds, dx
	mov	  es, dx
	mov	  fs, dx
	mov   edx,esi
	
  mov     esi,esp	
    			
	push	restart				
	jmp	[esi + RETADR - P_STACKBASE]	;跳回hwint_master 	

restart:
	pop	gs
	pop	fs
	pop	es
	pop	ds
	popad
	add	esp, 4
	iretd

; ========================================================================
;                  i8259A中断 
; ========================================================================    						
%macro	hwint_master	3            ;中断号，中断屏蔽端口，中断控制器 
	call	save
	
	;屏蔽当前的中断 
	;in	al, %2	
	;or	al, (1 << %1)	
	;out	%2, al
	
	;开启中断 
	mov	al, EOI		
	out	%3, al		
	;sti	
	
	;调用中断 
	push	%1			
	call	[irq_table + 4 * %1]
	pop	ecx	
    		
	;cli
	;开启中断 
	;in	al, %2	
	;and	al, ~(1 << %1)		
	;out	%2, al	
	ret
%endmacro

Timer_intr:
     hwint_master     0,INT_M_CTLMASK,INT_M_CTL
     
Kerboard_intr:
     hwint_master     1,INT_M_CTLMASK,INT_M_CTL
     
Serial2_intr:
     push     3
     jmp      irq_intr
     
Serial1_intr:
     push     4
     jmp      irq_intr
     
Lpt2_intr:
     push     5
     jmp      irq_intr
     
Floppy_intr:
     hwint_master     6,INT_M_CTLMASK,INT_M_CTL

Lpt1_intr:
     push     7
     jmp      irq_intr
     
Real_intr:
     push     8
     jmp      irq_intr

Mouse_intr:
     push     12
     jmp      irq_intr
     
Fpu_intr:
     push     13
     jmp      irq_intr
     
Atwin_intr:
     hwint_master     0,INT_S_CTLMASK,INT_S_CTL

; ========================================================================
;                  0x00~0x0F中断 
; ========================================================================

no_error_code:
   pop    dword [ex_number] 
   mov    dword [trap_errno],0xFFFFFFFF
   jmp    excetion

error_code:
   pop    dword [ex_number]
   pop    dword [trap_errno]                 
   jmp    excetion

excetion:
   push   eax   
   mov    dword eax,[esp + 4]
   mov    dword [old_eip],eax
   mov    dword eax,[esp + 8]
   mov    dword [old_cs],eax   
   mov    dword eax,[esp + 12]
   mov    dword [old_eflags],eax   
   pop    eax
   call	  save
   push	  dword [old_eflags]
   push	  dword [old_cs]
   push	  dword [old_eip]
   push	  dword [trap_errno]
   push	  dword [ex_number]
   call   super_handler
   add    esp,4 * 5
   cli
   ret
   
divide_error:
   push  0
   jmp   no_error_code

single_step_exception:
   push  1
   jmp   no_error_code

nmi:
   push  2
   jmp   no_error_code

breakpoint_exception:
   push  3
   jmp   no_error_code

overflow:
   push  4
   jmp   no_error_code
   
bounds_check:
   push  5
   jmp   no_error_code
   
inval_opcode:
   push  6
   jmp   no_error_code
   
copr_not_available:
   push  7
   jmp   no_error_code
   
double_fault:
   push  8
   jmp   error_code
   
copr_seg_overrun:
   push  9
   jmp   no_error_code
   
inval_tss:
   push  10
   jmp   error_code
   
segment_not_present:
   push  11
   jmp   error_code
   
stack_exception:
   push  12
   jmp   error_code
   
general_protection:
   push  13
   jmp   error_code

page_fault:
   push  14
   jmp   error_code
   
copr_error:
   push  16
   jmp   no_error_code

; ========================================================================
;                  系统调用 
; ========================================================================
sys_call:
	call	save

  push  edx                                           ;ebx,ecx,edx作为参数
	push	ecx
	push	ebx
	call	[sys_call_table + eax * 4]
	add	esp, 4 * 3

	mov	[esi + EAXREG - P_STACKBASE], eax

	cli

	ret
; ========================================================================
;                  void disable_irq(int irq);
; ========================================================================
; Disable an interrupt request line by setting an 8259 bit.
; Equivalent code for irq < 8:
;       out_byte(INT_CTLMASK, in_byte(INT_CTLMASK) | (1 << irq));
; Returns true iff the interrupt was not already disabled.
;
Disable_irq:
	mov	ecx, [esp + 4]		; irq
	pushf
	cli
	mov	ah, 1
	rol	ah, cl			; ah = (1 << (irq % 8))
	cmp	cl, 8
	jae	disable_8		; disable irq >= 8 at the slave 8259
disable_0:
	in	al, INT_M_CTLMASK
	test	al, ah
	jnz	dis_already		; already disabled?
	or	al, ah
	out	INT_M_CTLMASK, al	; set bit at master 8259
	popf
	mov	eax, 1			; disabled by this function
	ret
disable_8:
	in	al, INT_S_CTLMASK
	test	al, ah
	jnz	dis_already		; already disabled?
	or	al, ah
	out	INT_S_CTLMASK, al	; set bit at slave 8259
	popf
	mov	eax, 1			; disabled by this function
	ret
dis_already:
	popf
	xor	eax, eax		; already disabled
	ret

; ========================================================================
;                  void enable_irq(int irq);
; ========================================================================
; Enable an interrupt request line by clearing an 8259 bit.
; Equivalent code:
;	if(irq < 8){
;		out_byte(INT_M_CTLMASK, in_byte(INT_M_CTLMASK) & ~(1 << irq));
;	}
;	else{
;		out_byte(INT_S_CTLMASK, in_byte(INT_S_CTLMASK) & ~(1 << irq));
;	}
;
Enable_irq:
        mov	ecx, [esp + 4]		; irq
        pushf
        cli
        mov	ah, ~1
        rol	ah, cl			; ah = ~(1 << (irq % 8))
        cmp	cl, 8
        jae	enable_8		; enable irq >= 8 at the slave 8259
enable_0:
        in	al, INT_M_CTLMASK
        and	al, ah
        out	INT_M_CTLMASK, al	; clear bit at master 8259
        popf
        ret
enable_8:
        in	al, INT_S_CTLMASK
        and	al, ah
        out	INT_S_CTLMASK, al	; clear bit at slave 8259
        popf
        ret
;===============================================================================
;				调用用户空间的应用程序					                                     
;===============================================================================
call_user:
        call 0x40000000
        ret

jmp_user:
        jmp 0x40000000

;===============================================================================
;				data					                                     
;===============================================================================
[SECTION .data]
[BITS 32]
Excetion:
	ex_number        dd           0
	trap_errno       dd           0
	old_eip          dd           0
	old_cs           dd           0
	old_eflags       dd           0   
