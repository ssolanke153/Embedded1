;ORG 00H 
;	
;RPT:	MOV A,#38H
;	ACALL COMMAND
;	
;	MOV A,0EH
;	ACALL COMMAND
;	
;	MOV A,01H
;	ACALL COMMAND
;	
;	MOV A,06H
;	ACALL COMMAND
;	
;	
;	LJMP MAIN
;	
;	
;	ORG 000BH
;		CPL P1.2
;		RETI
;		
;		ORG 0030H
;			MOV TMOD,#20H
;			
;MAIN:		MOV TH0,#0B6H
;			MOV IE,#82H
;			SETB TR0
;			
;        	MOV P0,#"Y"
;            ACALL DISPLAY
;			SJMP RPT
;			
;COMMAND:
;         MOV P0,A
;         CLR P3.0
;		 CLR P3.1
;		 SETB P3.2
;		 CLR P3.2
;		 RET 
;		 
;DISPLAY:
;        MOV P0,#'A'
;        SETB P3.0
;		CLR P3.1
;		SETB P3.2
;		 CLR P3.2
;		 RET
;	
;		
;			END
;




;ORG 00H 
;	LJMP MAIN
;	
;	ORG 0003H
;LED1:	MOV P0,#0FFH
;		MOV R0,#255
;		DJNZ R0,LED1
;RETI

;ORG 0013H 
;LED2:	MOV P2,#0FFH
;	MOV R0,#255
;	DJNZ R0,LED2
;	RETI 
;	
;	ORG 0030H
;MAIN:	MOV IE,#85H
;HERE:		SJMP HERE
;		END


ORG 0000H
	LJMP MAIN
	
	ORG 0013H
		SETB P2.6
		CLR P2.7
		MOV R5,#255
		MOV R2,255
		
		BACK: DJNZ R5,BACK
		CLR P2.6
		SETB P2.7
		RETI 
		
		ORG 30H
			MAIN:MOV IE,#10000100B
			HERE: SJMP HERE 
			END