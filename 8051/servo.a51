ORG 00H
	
	MAIN:
	CLR P2.0
	ACALL DELAY
	SETB P2.0
	
	ACALL DELAY
	
	CLR P2.0
	SETB P2.0
	ACALL DELAY
	
	
	
    ;ACALL DELAY 
	SJMP MAIN
	
	
	DELAY:
	MOV R2,#10
	H3:MOV R0,#255
	
	H2:MOV R1,#255
	
	H1:DJNZ R1,H1
	DJNZ R0,H2
	DJNZ R2,H3
	RET
	
	END