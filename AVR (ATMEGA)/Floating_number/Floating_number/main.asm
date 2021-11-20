;
; Floating_number.asm
;
; Created: 7/16/2020 1:08:14 PM
; Author : Shri
;


 
.INCLUDE"M32DEF.INC"

.ORG 0

RJMP MAIN

BIT4CMD:


SBRS R16, 0
RJMP else
SBI PORTC, 4
RJMP if1

else:
CBI PORTC, 4

if1:
SBRS R16, 1
RJMP else1
SBI PORTC, 5
RJMP if2

else1:
CBI PORTC, 5

if2:
SBRS R16, 2
RJMP else2
SBI PORTC, 6
RJMP if3

else2:
CBI PORTC, 6

if3:
SBRS R16, 3
RJMP else3
SBI PORTC, 7
RJMP ena

else3:
CBI PORTC, 7

ena:
SBI PORTD, 6
CBI PORTD, 6

RCALL DELAY
RET

SENDCMD:

MOV R28, R16
CBI PORTD, 4
SWAP R16
ANDI R16, 0x0F
RCALL BIT4CMD

MOV R16, R28
RCALL BIT4CMD
RET

SENDATA:

MOV R28, R16
SBI PORTD, 4
SWAP R16
ANDI R16, 0x0F
RCALL BIT4CMD
MOV R16, R28
RCALL BIT4CMD
RET

MAIN1:

SBI DDRD, 4
SBI DDRD, 6

SBI DDRC, 4
SBI DDRC, 5
SBI DDRC, 6
SBI DDRC, 7

CBI PORTD, 4
CBI PORTD, 6

LDI R16, 0x02
RCALL SENDCMD

LDI R16, 0x28
RCALL SENDCMD

LDI R16, 0x0C  
RCALL SENDCMD

LDI R16, 0x06
RCALL SENDCMD
RET


HERE1:

MAIN:

RCALL MAIN1

 

LDI ZH, HIGH(MYDATA<<1)
LDI ZL, LOW(MYDATA<<1)

 

DATA:

LPM R16, Z
CPI R16, 0
BREQ HERE
RCALL SENDATA
INC ZL
RCALL DELAY
RJMP DATA

HERE: 


LDI R24, 0
OUT DDRA, R24

LDI R24, 0x87
OUT ADCSRA, R24

LDI R24, 0xE0
OUT ADMUX, R24

READ_ADC:

LDI R16, 0x85
CALL SENDCMD


SBI ADCSRA, ADSC

KEEP_POLLING:
SBIS ADCSRA, ADIF
RJMP KEEP_POLLING
SBI ADCSRA, ADIF
IN R24, ADCH
SWAP R24
ANDI R24, 0x0F
ORI R24, 0x30


MOV R16, R24
CALL SENDATA

RJMP READ_ADC
RJMP HERE


DELAY:
LDI R20, 10
H3: LDI R18, 30
H2: LDI R19, 50

H1: 
DEC R19
BRNE H1

DEC R18
BRNE H2

DEC R20
BRNE H3
RET
 
 .ORG 0x100
  
 MYDATA: .DB "TEMP:",0

.EXIT
