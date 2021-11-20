;
; ADC1.asm
;
; Created: 6/12/2020 3:01:36 PM
; Author : Shri
;


; Replace with your application code
 .INCLUDE "M32DEF.INC"

    LDI R16, 0xFF
	OUT DDRB,  R16
	OUT DDRD, R16
	LDI R16, 0
	OUT DDRA, R16
	LDI R16, 0x87
	OUT ADCSRA, R16
	LDI R16, 0xC0
	OUT ADMUX, R16

READ_ADC:
    SBI ADCSRA, ADSC

KEEP_POLLING:
    SBIS ADCSRA, ADIF
	RJMP KEEP_POLLING
	SBI ADCSRA, ADIF
	IN R16, ADCL
	OUT PORTD, R16
	IN R16, ADCH
	OUT PORTB, R16
	RJMP READ_ADC


.EXIT