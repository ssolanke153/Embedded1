;
; square_wave_at_OC0.asm
;
; Created: 6/30/2020 9:50:59 AM
; Author : Shri
 

 /* USING NORMAL MODE*/

/* .INCLUDE "M32DEF.INC"

 CBI DDRB, 0
 SBI DDRB, 3

 LDI R20, 200
 OUT OCR0, R20

 LDI R20, 0x11
 OUT TCCR0, R20

 HERE:
  RJMP HERE
  */

/* USIN CTC MODE*/

/*.INCLUDE "M32DEF.INC"

 CBI DDRB, 0
 SBI DDRB, 3

 LDI R20, 200
 OUT OCR0, R20

 LDI R20, 0x19
 OUT TCCR0, R20

 HERE:
  RJMP HERE*/


  /* DIFFERENT WIDTH OF SQUARE WAVE*/

.INCLUDE "M32DEF.INC"

.ORG 0

SBI DDRB, 3

START:
LDI R20 ,0
OUT TCNT0, R20
LDI R20, 0x69
OUT OCR0, R20

LDI R20, 0x19
OUT TCCR0, R20

L1:IN R20, TIFR
SBRS R20, OCF0
RJMP L1

LDI R16, 1<<OCF0
OUT TIFR, R16

LDI R20 ,0
OUT TCNT0, R20

LDI R20, 0x99
OUT OCR0, R20

LDI R20, 0x19
OUT TCCR0, R20
L2: IN R20, TIFR
SBRS R20, OCF0
RJMP L2

LDI R16, 1<<OCF0
OUT OCR0, R16

RJMP START

