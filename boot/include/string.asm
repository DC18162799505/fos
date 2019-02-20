;===============================================================================
;VERSION    0.1
;===============================================================================

;-------------------------------------------------------------------------------
%macro Position 2           ;position in video buffer and return edi
       mov dword edi,(%1 * 80 + %2) * 2         ;return value in edi
%endmacro
;-------------------------------------------------------------------------------
; display a character
;-------------------------------------------------------------------------------
%macro Video_buffer 4       ;charater£ºattibute£ºline: row  with base in gs 
       push  es             ;return value in edi
       push  dx
       
       mov   byte dh,%2
       mov   byte dl,%1
       Position %3,%4
       mov   word [gs:edi],dx
       
       pop   dx
       pop   es 
%endmacro

%macro Video_buffer 3       ;charater£ºattibute£ºoffset with base in gs
       push  dx
       push  eax
       
       xor   eax,eax
       mov   byte dh,%2
       mov   byte dl,%1
       mov   word ax,%3
       mov   edi,eax
       mov   word [gs:edi],dx
       
       pop   eax
       pop   dx      
%endmacro

%macro Video_buffer 2       ;charater£ºattibute with base in gs
       push  dx             ;offset in edi
       
       mov   byte dh,%2
       mov   byte dl,%1
       mov   word [gs:edi],dx
       add   edi,2
       
       pop   dx      
%endmacro
;-------------------------------------------------------------------------------
; display a string and end with '$'
;-------------------------------------------------------------------------------
%macro Displaystr 3         ;Str offset: line: row with base in gs
       push  cx
       push  ebx
       
       xor   cx,cx
       mov   dword ebx,%1
       mov   word cx,(%2 * 80 + %3) * 2
  %%loop:
       Video_buffer [ebx],0ch,cx     
       add   cx,2
       inc   ebx
       cmp   byte [ebx],'$'
       jnz   %%loop
       
       pop   ebx
       pop   cx
%endmacro

%macro Displaystr 1         ;Str offset with base in gs
       push  ebx           ;address in edi
       
       mov   dword ebx,%1
  %%loop:
       Video_buffer [ebx],0ch     
       inc   ebx
       cmp   byte [ebx],'$'
       jnz   %%loop
       
       pop   ebx
%endmacro
;-------------------------------------------------------------------------------
; display a space
;-------------------------------------------------------------------------------
%macro Displayspace 0
       push  ax
       
       mov   ah,00h;
       mov   al,' '
       mov   [gs:edi],ax
       add   edi,2
       
       pop   ax
%endmacro
;-------------------------------------------------------------------------------
; return in the next line
;-------------------------------------------------------------------------------
%macro Disreturn 0
       push  eax
       push  ebx
       
       mov   eax,edi
       mov   bl,160
       div   bl
       and   eax,0FFH
       inc   eax
       mul   bl
       mov   edi,eax
       
       pop   ebx
       pop   eax
%endmacro
;-------------------------------------------------------------------------------
; display a number in hex
;-------------------------------------------------------------------------------
%macro Displaynum  2
       push	 ecx
       push  eax
       		
	   mov   byte al, %1
	   shr   al, 4
	   mov	 byte ah, %2	
	   mov   ecx,2
%%begin:
	   and 	 al, 01111b
	   cmp	 al, 9
	   ja	 %%1
	   add	 al, '0'
	   jmp	 %%2
%%1:
	   sub	 al, 0Ah
	   add   al, 'A'
%%2:
	   mov	 [gs:edi], ax
	   add	 edi, 2

	   mov	 byte al, %1
	   loop	 %%begin
  
       pop   eax
	   pop	 ecx
%endmacro
;-------------------------------------------------------------------------------
; display a integer in hex
; integer:colour 
;-------------------------------------------------------------------------------
%macro Displayint  2
       push  ebx
       
       mov   dword  ebx,%1
       shr   ebx, 24
       Displaynum  bl, %2
        
       mov   dword  ebx,%1
       shr   ebx, 16
       Displaynum  bl, %2
       
       mov   dword  ebx,%1
       shr   ebx, 8
       Displaynum  bl, %2
       
       mov   dword  ebx,%1
       Displaynum  bl, %2
       
       Video_buffer  'h',0ch
              
       pop   ebx
%endmacro
;-------------------------------------------------------------------------------
; void* MemCpy(void* es:pDest, void* ds:pSrc, int iSize);
;-------------------------------------------------------------------------------
%macro  Memcpy  3
        push    esi
        push    edi
       
        mov     dword edi,%1
        mov     dword esi,%2
        mov     dword ecx,%3
%%loop:
        mov     al,[ds:esi]
        mov     [es:edi],al
        inc     edi
        inc     esi
        loop    %%loop
       
        pop     edi
        pop     esi
%endmacro
;-------------------------------------------------------------------------------
