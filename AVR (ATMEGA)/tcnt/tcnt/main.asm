;
; tcnt.asm
;
; Created: 14-05-2020 23:51:01
; Author : Shri
;

 .ORG $0

 LDI R20,0x50
 OUT TCNT0,R20
 IN R25,TCNT0
 HERE:RJMP HERE