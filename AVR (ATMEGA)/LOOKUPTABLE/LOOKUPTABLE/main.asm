;
; LOOKUPTABLE.asm
;
; Created: 08-05-2020 8.49.40 PM
; Author : Shri
;
LDI ZL,LOW(MYDATA)
LDI ZH,HIGH(MYDATA)
LDI R17,4
H1:LPM R16,Z+
INC ZL
DEC R17
BRNE H1

 .ORG $220
MYDATA:
         .DB '1','2','3','4'
		  
		/*  CLC
		  SEC
		  LDI R20,0xF9
	      ASR R20
		  ASR R20
		  ASR R20
		  ASR R20
		  ASR R20
		  ASR R20*/

		  