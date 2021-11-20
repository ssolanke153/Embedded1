;
; macros.asm
;
; Created: 11-05-2020 1.54.08 AM
; Author : Shri




 

 .INCLUDE "M32DEF.INC"

 .MACRO SHRI
 LDI R21,@1
 OUT @0,R21

 .ENDMACRO
 

 .MACRO DELAY
   LDI @0,@1

   BACK:
   NOP
   NOP
   NOP
   NOP
   DEC @0
   BRNE BACK
   .ENDMACRO


   .ORG 0
   SHRI DDRB,0xFF
 L1:  SHRI PORTB,0x55
   DELAY R18,0x70
   SHRI PORTB,0xAA
   DELAY R18,0x70
   RJMP L1