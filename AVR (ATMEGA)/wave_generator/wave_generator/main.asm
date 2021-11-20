;
; wave_generator.asm
;
; Created: 6/30/2020 9:01:49 AM
; Author : Shri
 
 .INCLUDE"M32DEF.INC"

 .org 0

 CBI DDRB, 0
 SBI DDRB, 3

 LDI R20, 1
 OUT OCR0, R20

 LDI R20, 0
 OUT TCNT0, R20

 LDI R20, 0x1E
 OUT TCCR0, R20

 HERE:
 RJMP HERE