;===============================================================================
;VERSION    0.1
;===============================================================================

%include         "desmacro.inc"
;-------------------------------------------------------------------------------
%macro   Loaddec       2                            ; Label:Decriptor
         xor     eax,eax
         mov     ax,cs
         shl     eax,4
         add     eax,%1
         mov     word [%2 + 2],ax
         shr     eax,16
         mov     byte [%2 + 4],al
         mov     byte [%2 + 7],ah
%endmacro
;-------------------------------------------------------------------------------
%macro   Loadgdt       2
         xor    eax,eax
         mov    ax,cs
         shl    eax,4
         add    eax,%1
         mov    dword [%2 + 2],eax
         lgdt   [%2]         
%endmacro
;-------------------------------------------------------------------------------
%macro   Loadidt       2
         xor    eax,eax
         mov    ax,cs
         shl    eax,4
         add    eax,%1
         mov    dword [%2 + 2],eax
         lidt   [%2]         
%endmacro
;-------------------------------------------------------------------------------
%macro   Loadldt       1
         mov    ax,%1
         lldt   ax
%endmacro
;-------------------------------------------------------------------------------
%macro   Loadtr        1
         mov    ax,%1
         ltr    ax
%endmacro
;-------------------------------------------------------------------------------
