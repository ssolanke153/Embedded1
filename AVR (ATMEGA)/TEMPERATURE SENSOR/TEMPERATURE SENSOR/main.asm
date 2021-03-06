;
; TEMPERATURE SENSOR.asm
;
; Created: 6/13/2020 3:34:24 PM
; Author : Shri
 

 .INCLUDE "M32DEF.INC"

LDI R16,0xFF
OUT DDRB,R16

 
 


 LDI R17,0x38
 RCALL COMMAND

 LDI R17,0x01
 RCALL COMMAND

 LDI R17,0x0C
 RCALL COMMAND

 LDI R17,0x06
 RCALL COMMAND

 LDI R17,0x80
 RCALL COMMAND

 


    LDI R16, 0xFF
	OUT DDRD, R16
	LDI R16, 0
	OUT DDRA , R16

	LDI R16, 0x87
	OUT ADCSRA, R16

	LDI R16, 0xE0
	OUT ADMUX, R16

READ_ADC:
     
	 LDI R17,0x01
     RCALL COMMAND
     SBI  ADCSRA, ADSC

KEEP_POLING:
     SBIS ADCSRA, ADIF
	 RJMP  KEEP_POLING
	 SBI ADCSRA, ADIF
	 IN R16, ADCH
	  

	 RCALL CONV
	 ;RCALL DISPLAY
	
	 RJMP  READ_ADC


CONV:
    
     ORI R16, 0x30
	 RCALL DISPLAY
	 
	  RET

DISPLAY:
   OUT PORTD, R16
 SBI PORTB,0
 CBI PORTB,1
 SBI PORTB,2
 CBI PORTB,2
 LDI R22, 250
L1: RCALL DELAY
 DEC R22
 BRNE L1

 RET


 COMMAND:
 OUT PORTD,R17
 CBI PORTB,0
 CBI PORTB,1
 SBI PORTB,2
 CBI PORTB,2
 RCALL DELAY
 RET

 DELAY:

       LDI R27,10
H2:	   LDI R26,100

H1:	   DEC R26
	   BRNE H1

	   DEC R27
	   BRNE H2

	   RET

MYDATA:
      
	  .DB "TEMPERATURE =  ", 0

	  RET

