;
; DAC.asm
;
; Created: 6/14/2020 5:22:46 PM
; Author : Shri
 

 .ORG 0

   LDI R16, 0xFF
   OUT DDRB, R16

AGAIN:
   INC R16
   OUT PORTB, R16
   NOP
   NOP
   RJMP AGAIN

.EXIT