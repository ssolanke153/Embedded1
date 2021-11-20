;
; RTC_TIME(done).asm
;
; Created: 06-08-2020 08:07:38 AM
; Author : Shri
;

.INCLUDE"M32DEF.INC"
RJMP MAIN



send_cmd:

		CBI PORTB, 0
		CBI PORTB, 1
		SBI PORTB, 2
		CBI PORTB, 2

       RCALL delay

	RET


lcd_init:
		LDI R24, 0xFF
		OUT 0x17, R24
		OUT 0x11, R24
		LDI R24, 0x38
		OUT 0x12, R24
		RCALL send_cmd

		LDI R24, 0x80
		OUT 0x12, R24
		RCALL send_cmd
		
		LDI  R24,  0x0C
		OUT 0x12, R24
		RCALL send_cmd

		LDI R24, 0x06
		OUT 0x12, R24
		RCALL send_cmd

	RET

lcd_send_data:
		SBI 0x18, 0
		CBI 0x18, 1
		SBI 0x18, 2
		CBI 0x18, 2
		RCALL delay
		RET

delay:		
LDI R24, 0x9F
		LDI R25, 0x0F
WAIT1:
        
		SBIW R24, 0x01
		BRNE WAIT1

	RET
		
usart_send_packedBCD:
		PUSH R28
		MOV R28, R24
		SWAP R24
		ANDI R24, 0x0F
		ORI R24, 0x30
		OUT 0x12, R24
		RCALL lcd_send_data

		ANDI R28, 0x0F
		ORI R28, 0x30

		OUT 0x12, R28
		RCALL lcd_send_data

		POP R28
	RET





i2c_init:
		OUT TWSR, R1
		LDI R24, 0x47
		OUT 0x00, R24

		LDI R24, 0x04
		OUT TWCR, R24
	 RET

i2c_start:
		LDI R24, (1<<TWINT) | (1<<TWSTA) | (1<<TWEN)
		OUT TWCR, R24

CHE1:   IN R0, 0x36
		SBRS R0, 7
		RJMP CHE1

     RET


i2c_write:
		OUT TWDR, R24

		LDI R24, (1<<TWINT) | (1<<TWEN)
		OUT TWCR, R24

CHE2:	IN R0, TWCR
		SBRS R0, 7
		RJMP CHE2

	RET


i2c_read:
		LDI R18, 0x40
		MUL R24, R18
		MOVW R24, R0
		EOR R1, R1
		ORI R24, 0x84
		OUT TWCR, R24

CHE3:	IN R0, TWCR
		SBRS R0, 7
		RJMP CHE3
		IN R24, 0x03

	RET

i2c_stop:
		LDI R24, (1<<TWINT) | (1<<TWEN) | (1<<TWSTO)
		OUT TWCR, R24
		LDI R24, 0x64
		LDI R25, 0x00
WAIT:
		SBIW R24, 0x01
		BRNE WAIT

	RET

rtc_init:
		RCALL i2c_init
		RCALL i2c_start

		LDI R24, 0xD0
		RCALL i2c_write

		LDI R24, 0x07
		RCALL i2c_write

		LDI R24, 0x00
		RCALL i2c_write

		RCALL i2c_stop

	RET

rtc_setTime:
		PUSH R17
		PUSH R28
		PUSH R29
		MOV R28, R24
		MOV R29, R22
		MOV R17, R20 
		RCALL i2c_start

		LDI R24, 0xD0
		RCALL i2c_write

		LDI R24, 0x00
		RCALL i2c_write

		MOV R24, R17
		RCALL i2c_write

		MOV R24, R29
		RCALL i2c_write

		MOV R24, R28
		RCALL i2c_write

		 
		RCALL i2c_stop

		POP R29
		POP R28
		POP R17
	RET

rtc_setDate:
		PUSH R17
		PUSH R28
		PUSH R29
		MOV R28, R24
		MOV R29, R22
		MOV R17, R20

		RCALL i2c_start

		LDI R24, 0xD0
		RCALL i2c_write

		LDI R24, 0x04
		RCALL i2c_write

		MOV R24, R17
		RCALL i2c_write

		MOV R24, R29
		RCALL i2c_write

		MOV R24, R28
		RCALL i2c_write

		RCALL i2c_stop

		POP R29
		POP R28
		POP R17
	RET

rtc_getTime:
		PUSH R14
		PUSH R15
		PUSH R16
		PUSH R17
		PUSH R28
		PUSH R29
		MOVW R28, R24
		MOVW R16, R22
		MOVW R14, R20

		RCALL i2c_start

		LDI R24, 0xD0
		RCALL i2c_write

		LDI R24, 0x00
		RCALL i2c_write

		RCALL i2c_stop

		RCALL i2c_start

		LDI R24, 0xD1
		RCALL i2c_write

		LDI R24, 0x01
		RCALL i2c_read
		MOVW R30, R14
		ST Z, R24

		LDI R24, 0x01
		RCALL i2c_read
		MOVW R30, R16
		ST Z, R24

		LDI R24, 0x00
		RCALL i2c_read

		ST Y, R24
		RCALL i2c_stop

		POP R29
		POP R28
		POP R17
		POP R16
		POP R15
		POP R14
	RET

rtc_getDate:
		PUSH R14
		PUSH R15
		PUSH R16
		PUSH R17
		PUSH R28
		PUSH R29
		MOVW R28, R24
		MOVW R16, R22
		MOVW R14, R20

		RCALL i2c_start

		LDI R24, 0xD0
		RCALL i2c_write

		LDI R24, 0x04
		RCALL i2c_write

		RCALL i2c_stop


		RCALL i2c_start

		LDI R24, 0xD1
		RCALL i2c_write

		LDI R24, 0x01
		RCALL i2c_read
		MOVW R30, R14
		ST Z, R24

		LDI R24, 0x01
		RCALL i2c_read
		MOVW R30, R16
		ST Z, R24

		LDI R24, 0x00
		RCALL i2c_read
		ST Y, R24
		RCALL i2c_stop

		POP R29
		POP R28
		POP R17
		POP R16
		POP R15
		POP R14
	RET


MAIN: 
		PUSH R28
		PUSH R29
		PUSH R1
		IN R28, 0x3D
		IN R29, 0x3E

		RCALL rtc_init

		LDI R20, 0x57
		LDI R22, 0x59
		LDI R24, 0x05
		RCALL rtc_setTime

		LDI R20, 0x20
		LDI R22, 0x8
		LDI R24, 0x05
		RCALL rtc_setDate
		RCALL lcd_init

		MOVW R20, R28
		SUBI R20, 0xFD
		SBCI R21, 0xFF
		MOVW R22, R28
		SUBI R22, 0xFE
		SBCI R23, 0xFF
		MOVW R24, R28
		ADIW R24, 0x1
		RCALL rtc_getTime

		LDD R24, Y+1
		RCALL usart_send_packedBCD

		LDI R17, 0x3A
		OUT 0x12, R17
		RCALL lcd_send_data

		LDD R24, Y+2
		RCALL usart_send_packedBCD

		OUT 0x12, R17
		RCALL lcd_send_data

		LDI R24, 0xC0
		OUT 0x12, R24
		RCALL send_cmd

		MOVW R20, R28
		SUBI R20, 0xFD
		SBCI R21, 0xFF
		MOVW R22, R28
		SUBI R22, 0xFE
		SBCI R23, 0xFF
		MOVW R24, R28
		ADIW R24, 0x01
		RCALL rtc_getDate

		LDD R24, Y+1
		RCALL usart_send_packedBCD

		OUT 0x12, R17
		RCALL lcd_send_data

		LDD R24, Y+2
		RCALL usart_send_packedBCD

		OUT 0x12, R17
		RCALL lcd_send_data

		LDD R24, Y+3
		RCALL usart_send_packedBCD

		LDI R17, 0x86
		MOV R0, R31
		LDI R31, 0x83
		MOV R15, R31
		MOV R3, R0

sec2:	LDI R16, 0x3A
sec1:	MOVW R20, R28
		SUBI R20, 0xFD
		SBCI R21, 0xFF
		MOVW R22, R28
		SUBI R22, 0xFE
		MOVW R24, R28
		ADIW R24, 0x01
		RCALL rtc_getTime

		OUT 0x12, R17
		RCALL send_cmd

		LDD R24, Y+3
		RCALL usart_send_packedBCD

		LDD R24, Y+3
		CPSE R24, R1
		RJMP sec1

		OUT 0x12, R15
		RCALL send_cmd

		LDD R24, Y+2
		RCALL usart_send_packedBCD

		OUT 0x12, R16
		RCALL lcd_send_data

		LDD R24, Y+2
		CPSE R24, R1
		RJMP sec1

		LDI R24, 0x80
		OUT 0x12, R24
		RCALL send_cmd

		LDD R24, Y+1
		RCALL usart_send_packedBCD

		LDI R24, 0x3A
		OUT 0x12, R24
		RCALL lcd_send_data

		RJMP sec2
		CLI 
HERE:   RJMP HERE
