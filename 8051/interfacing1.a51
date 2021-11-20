ORG 00H

MAIN:       MOV A,#38H
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
			
			CJNE A,#01000011B,JP2
			AJMP MAIN
		    
JP2:
		    CJNE A,#00111101B,JP1
			ACALL DISPLAY
			LJMP PERFORM
		
			
JP1:		ACALL DISPLAY	
			CJNE  A,#00101011B,VAJABAKI
			MOV R5,A
			SJMP N_3
VAJABAKI:	
            CLR C
            CJNE A,#00101101B,GUNAKAR
            MOV R5,A
			SJMP N_3
			
GUNAKAR:	CLR C
            CJNE A,#00101010B,BHAGAKAR
            MOV R5,A
			SJMP N_3
BHAGAKAR:	CLR C
            CJNE A,#00101111B,NUM
            MOV R5,A
			SJMP N_3
			
NUM:	    CLR C
            JNB PSW.1,CONV1        
            JB PSW.1,CONV2      		
N_3:        LJMP K1
			
CONV1:
            ANL A,#0FH
            MOV	R3,A
   			CLR  A
			CLR PSW.1
			SETB PSW.1 
			AJMP K1
			
CONV2:
            ANL A,#0FH
            MOV	R4,A
			CLR PSW.1
			CLR A
			AJMP K1
			
PERFORM:	
            CJNE R5,#00101011B,MINUS
			SJMP ADDITION
			
MINUS: 		
            CJNE R5,#00101101B,MULTYPLY
            SJMP SUBSTRACTION

MULTYPLY:   
            CJNE R5,#00101010B ,DIVIDE
            SJMP MULTIPLICATION


;            MOV A,R3
;	    	MOV B,R4
;			MUL AB
;            ACALL ANTICONV1
			 		
     		;AJMP K1
			
DIVIDE:    
          MOV A,R3
           MOV B,R4
		   DIV AB
		   ACALL ANTICONV2
		   AJMP K1 


ADDITION:	MOV A,R3
			ADD A,R4
            ACALL  ANTICONV
            AJMP K1	
           		
SUBSTRACTION:	
            MOV A,R3
			SUBB A,R4
            ACALL  ANTICONV
            AJMP K1

MULTIPLICATION:
                
			MOV A,R3
	    	MOV B,R4
			MUL AB
            ACALL ANTICONV1
			 		
     		AJMP K1
			
;DIVIDETATION:			
;           MOV A,R3
;           MOV B,R4
;		   DIV AB
;		   ACALL ANTICONV2
;		   AJMP K1
;   
 
			
			
ANTICONV:   MOV B,#10
            DIV AB
			ORL A,#30H
			ACALL DISPLAY
			MOV A,B
			ORL A,#30H
			ACALL DISPLAY
			RET
ANTICONV1:	
            MOV R6,B
			MOV R5,A
			CLR A
			MOV A,R6
			MOV B,#10
			DIV AB
			ORL A,#30H
			CJNE A,#30H,NEXT
		   ; ACALL DISPLAY
			
N_1:        MOV A,B
			ORL A,#30H
			CJNE A,#30H,NEXT1		
			;ACALL DISPLAY			
		
N_2:        CLR 0F0H
            MOV A,R5
			MOV B,#10
			DIV AB
			ORL A,#30H
             ACALL DISPLAY
            MOV A,B
			ORL A,#30H
			ACALL DISPLAY
            AJMP K1
			
			
			
NEXT:     
     ACALL DISPLAY
     SJMP N_1

NEXT1:     
     ACALL DISPLAY
     SJMP N_2
			
ANTICONV2:	
           
		   MOV B,#10
		   DIV AB
		   ORL A,#30H
		   ACALL DISPLAY
		   
		   MOV A,B
		   ORL A,#30H
		   ACALL DISPLAY
		   AJMP K1
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
            
		    MOV  R0,#20
AGAIN1:     MOV  R1,#200
AGAIN:      DJNZ R1,AGAIN
            DJNZ R0,AGAIN1
            RET
			
			
ORG 100H
	
	KCODE0: DB '7','8','9','/'
	KCODE1:	DB '4','5','6','*'
	KCODE2: DB '1','2','3','-'
	KCODE3:	DB 'C','0','=','+'
		
		RET 
END