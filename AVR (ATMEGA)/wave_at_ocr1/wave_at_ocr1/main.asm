;
; wave_at_ocr1.asm
;
; Created: 7/1/2020 5:09:42 PM
; Author : Shri
;

.INCLUDE "M32DEF.INC"

.ORG 0

SBI DDRD, 5

LDI R20, 0x40
OUT TCCR1A, R20

LDI R20, 0x01
OUT TCCR1B, R20

LDI R20, HIGH(65535)
OUT OCR1AH, R20

LDI R20, LOW(65535)
OUT OCR1AL, R20

HERE:
JMP HERE
