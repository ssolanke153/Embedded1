/*Ex. 1. WRITE A PROGRAM TO TRANSFER VALUE 41H SERIALLY VIA PIN P2.1. PUT TWO HIGHS AT THE
START AND END OF THE DATA. SEND THE BYTE LSB FIRST
*/
/*ORG 00H
	MOV A,#41H
	SETB P2.1
	SETB P2.1
	
	MOV R5,#8
	HERE: RRC A
	MOV P2.1,C
	DJNZ R5,HERE
	SETB P2.1
	SETB P2.1
	END
		*/
		
		
/*EX.2. WRITE A PROGRAM TO BRING IN DATA IN SERIAL FORM AND SEND IT OUT IN PARALLEL FORM.*/

/*ORG 00H
	
	MOV R0,#08
	SETB P0.0
BACK:MOV C,P0.0
	RRC A
	DJNZ R0,BACK
	MOV P1,A
	END
	*/
	
	/* SINGLE BIT OPERATIONS WITH CY*/
		
/* USING CARRY BIT OPERATIONS, WRITE  PROGRAM TO BLINK CONTINUOSLY AN LED CONNECTED TO P1.2 WITH A DELAY
	BETWEEN EACH ON AND OFF STATES OF HTE LED.
	*/
	
	ORG 00H
		BACK:CPL C
		MOV P1.2,C
	    ACALL DELAY
        SJMP BACK	
		DELAY:
		MOV R1,#255
			H2:MOV R0,#255
		H1:DJNZ R0,H1
		DJNZ R1,H2
		RET

END
		
		
		
		
		
		
		
		
		
		