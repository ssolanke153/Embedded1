ORG 0
	
	  MOV A,#38H
	  ACALL CMND
	
	  MOV A,#0FH 
	  ACALL CMND
	
	  MOV A,#01H
	  ACALL CMND
	
	  MOV A,#0CH
	  ACALL CMND
	
	  MOV A,#06H
	  ACALL CMND
	
	  MOV A,#80H
	  ACALL CMND
	  
	  
	  
	   MOV R0, #10
	   MOV A, #20H
	   MOVX @R0, A
      
      
        MOV R0, #11
        MOV A, #83H
        MOVX @R0, A

		MOV R0, #07
		MOV A, #24H
		MOVX @R0, A
		ACALL DELAY

		MOV R0 ,#08
		MOV A, #10H
		MOVX @R0, A
		ACALL DELAY
		MOV R0, #09
		MOV A,#04
		MOVX @R0, A
		ACALL DELAY
		MOV R0, #11
		MOV A,#03

OV1: 
		MOV A, #20H
		ACALL DISP

		MOV R0, #4
		MOVX A,@R0
		ACALL DISP1
		MOV A, #20H
		ACALL DISP
		MOV R0,#2
		MOVX A,@R0
		ACALL DISP1
		MOV A, #20H
		ACALL DISP
		MOV R0, #0
		MOVX A, @R0
		ACALL DISP1
		MOV A, #0AH
		ACALL DISP
		MOV A,#0DH
		ACALL DISP
		SJMP OV1

DISP1:
		  MOV B,A
		  SWAP A
		  ANL A,#0FH
		  ORL A,#30H
		  ACALL DISP
		  
		  MOV A,B
		  MOV A,#0FH
		  ORL A,#30H
		  ACALL DISP
		  RET
  
DISP:     MOV P2,A
		  SETB P1.0
		  CLR P1.1
		  SETB P1.2
		  CLR P1.2
		  ACALL DELAY 
		  RET  
	  	  
CMND:    
          MOV P2,A
		  CLR P1.0
		  CLR P1.1
		  SETB P1.2
		  CLR P1.2
		  ACALL DELAY
		  RET
	  
DELAY:    MOV R3,#0FFH
GO1:      MOV R2,#0FFH
GO:       DJNZ R2,GO
	      DJNZ R3,GO1
	
	      RET 
	  
	  
END