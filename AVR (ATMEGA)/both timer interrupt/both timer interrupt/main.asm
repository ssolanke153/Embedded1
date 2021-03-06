;
; both timer interrupt.asm
;
; Created: 22-05-2020 12:02:22
; Author : Shri

/*USES TIMER0 AND TIMER1 INTERRUPTS SIMULTANEOUSLY, TO GENERATE SQUARE WAVES ON PINS PB1 AND PB7 RESPECTIVELY,
WHILE DATA IS BEING TRANSFERED FROM PORTC TO PORTD*/


.INCLUDE "M32DEF.INC"

.ORG 0x00
JMP MAIN

.ORG 0x12
JMP T1_OV

.ORG 0x16
JMP T0_OV

.ORG 0x100

MAIN:
 LDI R20,HIGH(RAMEND)
 OUT SPH,R20

 LDI R20,LOW(RAMEND)
 OUT SPL,R20

 SBI DDRB,7
 SBI DDRB,1

 LDI R20,0x0
 OUT DDRC,R20

 LDI R20,0xFF
 OUT DDRD,R20

 LDI R20,(1<<TOIE0) | (1<<TOIE1)
 OUT TIMSK,R20
 SEI

 LDI R20,-160
 OUT TCNT0,R20

 LDI R20,0x01
 OUT TCCR0,R20


 LDI R20,HIGH(-640)
 OUT TCNT1H,R20

 LDI R20,LOW(-640)
 OUT TCNT1L,R20

 LDI R20,0x00
 OUT TCCR1A,R20

 LDI R20,0x01
 OUT TCCR1B,R20

 HERE: IN R20,PINC
       OUT PORTD,R20
	   JMP HERE


T0_OV:
  LDI  R16,-160
	  OUT TCNT0,R16
	  IN R16,PORTB
	  LDI R17,0x2

	  EOR R16,R17
	  OUT PORTB,R16

	  RETI





T1_OV:
       LDI R19,HIGH(-640)
	   OUT TCNT1H,R16

	   LDI R19,LOW(-640)
	   OUT TCNT1L,R16

	   LDI R19,PORTB
	   LDI R18,0X08
	   EOR R19,R18
	   OUT PORTB,R19

	   RETI

	   .EXIT


 