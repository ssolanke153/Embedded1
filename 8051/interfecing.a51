ORG 00H
			MOV A,#38H
			ACALL COMMAND

			MOV A,#01H
			ACALL COMMAND

			MOV A,#0CH
			ACALL COMMAND

			MOV A,#06H
			ACALL COMMAND

			MOV A,#80H
			ACALL COMMAND

            
			MOV P2,#0FFH 
K1:         MOV P0,#0
            
			MOV A,P2
			ANL A,#00001111B
			CJNE A,#00001111B,K1
K2:         ACALL DELAY
            
			MOV A,P2
			ANL A,#00001111B
			CJNE A,#00000111B,OVER
			SJMP K2
			
OVER:       ACALL DELAY 

			MOV A,P2
			ANL A,#00001111B
			CJNE A,#00001111B,OVER1
			SJMP K2
OVER1:      MOV P0,#11111110B
			MOV A,P2
			ANL A,#00001111B
			
			CJNE A,#00001111B,ROW_0
			MOV P0,#11111101B
			MOV A,P2
			ANL A,#00001111B
			
			CJNE A,#00001111B,ROW_1
			MOV P0,#11111011B
			MOV A,P2
			ANL A,#00001111B
			
			CJNE A,#00001111B,ROW_2
			MOV P0,#11110111B
			MOV A,P2
			ANL A,#00001111B
			CJNE A,#00001111B,ROW_3
			LJMP K2

ROW_0:      MOV DPTR,#KCODE0
            SJMP FIND
  
ROW_1:      MOV DPTR,#KCODE1
            SJMP FIND

ROW_2:      MOV DPTR,#KCODE2
            SJMP FIND

ROW_3:      MOV DPTR,#KCODE3
            SJMP FIND

FIND:       RRC A
			JNC MATCH
			INC DPTR
			SJMP FIND
			

MATCH:  
            
            CLR A
			
			MOVC A,@A+DPTR
			CJNE A,#101011B,SUBS
			SJMP SIGN1
L_1:		JB PSW.5,C2
			ACALL C1           			
JP:		    LJMP K1
			
C1:        MOV R4,A
           ACALL CONV
		  SETB PSW.5
         CLR A		  
		   RET
		   
C2:        MOV R5,A
           ACALL CONV
		   SJMP TEST1
		   RET
		   
TEST1:	   CJNE R6,#101011B,SUBES
		   SJMP PLUS
           CLR PSW.5
		   CLR A
		   CLR 0F0H
		   SJMP JP
 RET
  
SIGN1:     MOV R6,A
           ACALL DISPLAY 
           CLR A   
		   SJMP JP
		   RET
 
 
SUBS:      MOV R6,A
           CJNE A,#101101B,MULTI	   
		   RET
		   
MULTI:	   
           CJNE A,#101010B,DIVID
		   RET
		   		   
DIVID:	 
           CJNE A,#101111B,L_1
           RET
       
PLUS:      
           MOV A,R4
           ADD A,R5
		   ACALL CONV
		   RET
		   
SUBES:  
           CJNE R6,#101101B,MULTIPLY
           MOV A,R4
		   SUBB A,R5
		   ACALL CONV 
		   SJMP JP
		   RET	

MULTIPLY: NOP
;CJNE R6,#101010B,DIVIDE
;          MOV A,R4
;		  MOV B,R5
;		  MUL AB
;		  MOV A,B
;		  ACALL CONV
;		  SJMP JP 
;		  RET



;DIVIDE:  
;		NOP


;CJNE R6,#101111B,JP
;          MOV A,R4
;		  MOV B,R5
;		  DIV AB
;		  ACALL CONV
;		  SJMP JP
;		  RET
;		  
 CONV:
        MOV B,#10
		DIV AB
		ORL A,#30H 
        ACALL DISPLAY
		MOV A,B
		ORL A,#30H
		ACALL DISPLAY
		RET
		
 
COMMAND:
			MOV P1,A
			CLR P3.0
			CLR P3.1
			SETB P3.2
			CLR P3.2
			ACALL DELAY
			RET
DISPLAY:
			MOV P1,A
			SETB P3.0
			CLR P3.1
			SETB P3.2
			CLR P3.2
			ACALL DELAY
			RET
DELAY:
            
		    MOV  R0,#10
AGAIN1:     MOV  R1,#255
AGAIN:      DJNZ R1,AGAIN
            DJNZ R0,AGAIN1
            RET
			
			
ORG 100H
	
	KCODE0: DB 7,8,9,'/'
	KCODE1:	DB 4,5,6,'*'
	KCODE2: DB 1,2,3,'-'
	KCODE3:	DB ' ',0,'=','+'
		
		RET 
END

					 
					 
					 
					 
					 
					 