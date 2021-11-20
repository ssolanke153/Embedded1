;
; EEPROM.asm
;
; Created: 09-05-2020 8.43.46 PM
; Author : Shri


.INCLUDE "M32DEF.INC"

WAIT:

SBIC EECR,EEWE
RJMP WAIT

LDI R18,0x00
LDI R17,0x5F

OUT EEARH,R18
OUT EEARL,R17

LDI R16,'G'
OUT EEDR,R16

SBI EECR,EEMWE
SBI EECR,EEWE
 
 LDI R16,(1<<SREG_H) | (1<<SREG_S)
 OUT SREG,R16
 

SBI EECR,EERE
IN R20,EEDR
.EXIT 


 