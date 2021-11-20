;
; SPI.asm
;
; Created: 26-07-2020 09:20:44 PM
; Author : Shri
 


 .INCLUDE "M32DEF.INC"
 .equ MOSI = 5
 .equ SCK = 7
 .equ SS = 4


	LDI R17, 0xFF
	OUT DDRA, R17

	LDI R17, (1<<MOSI) | (1<<SCK) | (1<<SS)
	OUT DDRB, R17

	LDI R17, (1<<SPE) | (1<<MSTR) | (1<<SPR0)
	OUT SPCR, R17

	 
	
 LDI R27, 0x00
 RCALL Transmit
 CBR r27, 1
 RCALL Transmit
 SBR r27, 4
 RCALL Transmit
 CBR r27, 4
 RCALL Transmit

 LDI R27, 0x20
 RCALL Transmit
 CBR r27, 1
 RCALL Transmit
 SBR r27, 4
 RCALL Transmit
 CBR r27, 4
 RCALL Transmit

  LDI R27, 0x20
 RCALL Transmit
 CBR r27, 1
 RCALL Transmit
 SBR r27, 4
 RCALL Transmit
 CBR r27, 4
 RCALL Transmit

 LDI R27, 0x80
 RCALL Transmit
 CBR r27, 1
 RCALL Transmit
 SBR r27, 4
 RCALL Transmit
 CBR r27, 4
 RCALL Transmit


  LDI R27, 0x00
 RCALL Transmit
 CBR r27, 1
 RCALL Transmit
 SBR r27, 4
 RCALL Transmit
 CBR r27, 4
 RCALL Transmit

 LDI R27, 0xC0
 RCALL Transmit
 CBR r27, 1
 RCALL Transmit
 SBR r27, 4
 RCALL Transmit
 CBR r27, 4
 RCALL Transmit


  LDI R27, 0x00
 RCALL Transmit
 CBR r27, 1
 RCALL Transmit
 SBR r27, 4
 RCALL Transmit
 CBR r27, 4
 RCALL Transmit

 LDI R27, 0x60
 RCALL Transmit
 CBR r27, 1
 RCALL Transmit
 SBR r27, 4
 RCALL Transmit
 CBR r27, 4
 RCALL Transmit


  LDI R27, 0x30
 RCALL Transmit
 SBR r27, 1
 RCALL Transmit
 SBR r27, 4
 RCALL Transmit
 CBR r27, 4
 RCALL Transmit

 LDI R27, 0x50
 RCALL Transmit
 SBR r27, 1
 RCALL Transmit
 SBR r27, 4
 RCALL Transmit
 CBR r27, 4
 RCALL Transmit
 
 LDI R27, 0x30
 RCALL Transmit
 SBR r27, 1
 RCALL Transmit
 SBR r27, 4
 RCALL Transmit
 CBR r27, 4
 RCALL Transmit

 LDI R27, 0x60
 RCALL Transmit
 SBR r27, 1
 RCALL Transmit
 SBR r27, 4
 RCALL Transmit
 CBR r27, 4
 RCALL Transmit

LDI R27, 0x30
 RCALL Transmit
 SBR r27, 1
 RCALL Transmit
 SBR r27, 4
 RCALL Transmit
 CBR r27, 4
 RCALL Transmit

 LDI R27, 0x00
 RCALL Transmit
 SBR r27, 1
 RCALL Transmit
 SBR r27, 4
 RCALL Transmit
 CBR r27, 4
 RCALL Transmit

 LDI R27, 0x30
 RCALL Transmit
 SBR r27, 1
 RCALL Transmit
 SBR r27, 4
 RCALL Transmit
 CBR r27, 4
 RCALL Transmit

 LDI R27, 0x10
 RCALL Transmit
 SBR r27, 1
 RCALL Transmit
 SBR r27, 4
 RCALL Transmit
 CBR r27, 4
 RCALL Transmit

 LDI R27, 0x30
 RCALL Transmit
 SBR r27, 1
 RCALL Transmit
 SBR r27, 4
 RCALL Transmit
 CBR r27, 4
 RCALL Transmit

 LDI R27, 0x20
 RCALL Transmit
 SBR r27, 1
 RCALL Transmit
 SBR r27, 4
 RCALL Transmit
 CBR r27, 4
 RCALL Transmit



 HERE:RJMP HERE



	Transmit:
	CBI PORTB, SS
	OUT SPDR, R27
	wait:
	SBIS SPSR, SPIF
	RJMP wait
	LDI R17, (1<<SPIF)
 OUT SPSR, R17
	/*IN R18, SPDR
	OUT PORTA, R18*/
	;SBI PORTB, SS
	RET
