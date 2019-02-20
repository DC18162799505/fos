;===============================================================================
;VERSION    0.1
;===============================================================================


;===============================================================================
; CMOS INDEX 
;===============================================================================
%define          CMOS_PORT_OUT            70h
%define          CMOS_PORT_IN             71h

%define          TIME_SYSTEM_SECOND       00h
%define          TIME_ALARM_SECOND        01h
%define          TIME_SYSTEM_MINUTE       02h
%define          TIME_ALARM_MINUTE        03h
%define          TIME_SYSTEM_HOUR         04h
%define          TIME_ALARM_HOUR          05h

%define          TIME_SYSTEM_WEEK         06h         ;01 = SUNDAY , 02 TUESDAY , ect.

%define          TIME_SYSTEM_DATE         07h         ;00 ~ 31

%define          TIME_SYSTEM_MONTH        08h         ;01 ~ 12

%define          TIME_SYSTEM_YEAR         09h         ;00 = 2000,01 = 2001,ect.

;-------------------------------------------------------------------------------
; MEMORY SIZE
;-------------------------------------------------------------------------------
%define          T_LOWMEMORY               15h
%define          T_HIGHMEMORY              16h
%define          IBM_LOWMEMORY             17h
%define          IBM_HIGHMEMORY            18h
%define          POST_LOWMEMORY            35h
%define          POST_HIGHMEMORY           36h
