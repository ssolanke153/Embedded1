;
; floating_mul.asm
;
; Created: 17-07-2020 10:04:30 PM
; Author : Shri
;


; Demonstrates floating point conversion
; in Assembler, (C)2003 www.avr-asm-tutorial.net
;
; The task: You read in an 8-bit result of an
;    analogue-digital-converter, number is in the
;    range from hex 00 to FF.
;    You need to convert this into a floating point
;    number in the range from 0.00 to 5.00 Volt
;
; The program scheme:
;    1. Multiplication by 502 (hex 01F6).
;       That step multiplies by 500, 256 and
;       divides by 255 in one step!
;    2. Round the result and cut the last byte
;       of the result.
;       This step divides by 256 by ignoring the
;       last byte of the result. Before doing
;       that, bit 7 is used to round the result.
;    3. Convert the resulting word to ASCII and set
;       the correct decimal sign
;       The resulting word in the range from 0 to
;       500 is displayed in ASCII-characters as
;       0.00 to 5.00.
;
; The registers used:
;    The routines use the registers R8..R1 without
;    saving these before. Also required is a multi-
;    purpose register called rmp, located in the
;    upper half of the registers. Please take care
;    that these registers don't conflict with the
;    register use in the rest of your program.
;
;    When entering the routine the 8-bit number is
;    expected in the register R1.
;    The multiplication uses R4:R3:R2 to hold
;    the multiplicator 502 (is shifted left
;    max. eight times during multiplication).
;    The result of the multiplication is calculated
;    in the registers R7:R6:R5.
;    The result of the so called division by 256
;    by just ignoring R5 in the result, is in
;    R7:R6. R7:R6 is rounded, depending on the
;    highest bit of R5, and the result is copied to
;    R2:R1.
;    Conversion to an ASCII-string uses the input
;    in R2:R1, the register pair R4:R3 as a divisor
;    for conversion, and places the ASCII result
;    string to R5:R6:R7:R8 (R6 is the decimal char).
;
; Other conventions:
;   The conversion uses subroutines and the stack.
;   The stack must work fine for the use of three
;   levels (six bytes SRAM).
;
; Conversion times:
;   The whole routine requires 228 clock cycles
;   maximum (converting $FF), and 79 clock cycles
;   minimum (converting $00). At 4 MHz the times
;   are 56.75 microseconds resp. 17.75 microseconds.
;
; Definitions:
;   Registers
.DEF rmp = R16 ; used as multi-purpose register
;
;   AVR type
;   Tested for type AT90S8515, only required for
;   stack setting, routines work fine with other
;   AT90S-types also
.NOLIST
.INCLUDE "8515def.inc"
.LIST
;
; Start of test program
;
; Just writes a number to R1 and starts the
; conversion routine, for test purposes only
;
.CSEG
.ORG $0000
	rjmp main
;
main:
	ldi rmp,HIGH(RAMEND) ; Set the stack
	out SPH,rmp
	ldi rmp,LOW(RAMEND)
	out SPL,rmp
	ldi rmp,$FF ; Convert $FF
	mov R1,rmp
	rcall fpconv8 ; call the conversion routine
no_end:   ; unlimited loop, when done
	rjmp no_end
;
; Conversion routine wrapper, calls the different conversion steps
;
fpconv8:
        rcall fpconv8m ; multiplicate by 502
	rcall fpconv8r ; round and divide by 256
	rcall fpconv8a ; convert to ASCII string
	ldi rmp,'.' ; set decimal char
	mov R6,rmp
	ret ; all done
;
; Subroutine multiplication by 502
;
; Starting conditions:
; +--+
; |R1|  Input number, example is $FF
; |FF|
; +--+
; +--+--+--+
; |R4|R3|R2| Multiplicant 502 = $00 01 F6
; |00|01|F6|
; +--+--+--+
; +--+--+--+
; |R7|R6|R5| Result, as example 128,010
; |01|F4|0A|
; +--+--+--+
;
fpconv8m:
	clr R4 ; set the multiplicant to 502
	ldi rmp,$01
	mov R3,rmp
	ldi rmp,$F6
	mov R2,rmp
	clr R7 ; clear the result
	clr R6
	clr R5
fpconv8m1:
	or R1,R1 ; check if the number is all zeros
	brne fpconv8m2 ; still one's, go on convert
	ret ; ready, return back
fpconv8m2:
	lsr R1 ; shift number to the right (div by 2)
	brcc fpconv8m3 ; if the lowest bit was 0, then skip adding
        add R5,R2 ; add the number in R6:R5:R4:R3 to the result
	adc R6,R3
	adc R7,R4
fpconv8m3:
	lsl R2 ; multiply R4:R3:R2 by 2
	rol R3
	rol R4
	rjmp fpconv8m1 ; repeat for next bit
;
; Round the value in R7:R6 with the value in bit 7 of R5
;
fpconv8r:
	clr rmp ; put zero to rmp
	lsl R5 ; rotate bit 7 to carry
	adc R6,rmp ; add LSB with carry
	adc R7,rmp ; add MSB with carry
	mov R2,R7 ; copy the value to R2:R1 (divide by 256)
	mov R1,R6
	ret
;
; Convert the word in R2:R1 to an ASCII string in R5:R6:R7:R8
;
; +--+--+
; +R2|R1| Input value 0..500
; +--+--+
; +--+--+
; |R4|R3| Decimal divider value
; +--+--+
; +---+---+---+---+
; | R5| R6| R7| R8| Resulting ASCII string (for input value 5,00)
; |'5'|'.'|'0'|'0'|
; +---+---+---+---+
;
fpconv8a:
	clr R4 ; Set the decimal divider value to 100
	ldi rmp,100
	mov R3,rmp
	rcall fpconv8d ; get ASCII digit by repeated subtraction
	mov R5,rmp ; set hundreds string char
	ldi rmp,10 ; Set the decimal divider value to 10
	mov R3,rmp
	rcall fpconv8d ; get the next ASCII digit
	mov R7,rmp ; set tens string char
	ldi rmp,'0' ; convert the rest to an ASCII char
	add rmp,R1
	mov R8,rmp ; set ones string char
	ret
;
; Convert binary word in R2:R1 to a decimal digit by substracting
; the decimal divider value in R4:R3 (100, 10)
;
fpconv8d:
	ldi rmp,'0' ; start with decimal value 0
fpconv8d1:
	cp R1,R3 ; Compare word with decimal divider value
	cpc R2,R4
	brcc fpconv8d2 ; Carry clear, subtract divider value
	ret ; done subtraction
fpconv8d2:
	sub R1,R3 ; subtract divider value
	sbc R2,R4
	inc rmp ; up one digit
	rjmp fpconv8d1 ; once again
;
; End of floating point conversion routines
;
;
; End of conversion test routine
;
