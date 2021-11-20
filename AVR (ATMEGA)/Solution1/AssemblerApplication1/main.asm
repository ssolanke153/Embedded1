 .INCLUDE "m328pdef.inc"
 
 .ORG $0

 RJMP START

 START:
       LDI R16,3
	   LDI R17,$20
	   ADD R17,R16
	   

	   INC R17

	   FOREVER: RJMP FOREVER

	   .EXIT