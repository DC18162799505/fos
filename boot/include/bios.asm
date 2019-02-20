;===============================================================================
;VERSION    0.1
;===============================================================================
%include        "bios.inc"

%macro      MemorySize        0
      xor     eax,eax
      mov     al,IBM_HIGHMEMORY
      out     CMOS_PORT_OUT,al
      in      al,CMOS_PORT_IN
      shl     eax,8
      mov     al,IBM_LOWMEMORY
      out     CMOS_PORT_OUT,al
      in      al,CMOS_PORT_IN
%endmacro
