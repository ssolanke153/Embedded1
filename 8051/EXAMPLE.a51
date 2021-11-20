 ORG 00H
	 
	 MOV TMOD,#20H
	 MOV TH1,#-6
	 MOV SCON,#50H
	 SETB TR1
	 
	 MOV DPTR,#300H
H_1: MOVC A,@A+DPTR
     JZ H_2
	 
	 ACALL SEND
	 INC DPTR
	 CLR A
	 SJMP H_1
	 
H_2: 
     CALL RECEIVE
	 MOV P1,A
	 MOV P2,A
	 ACALL SEND



RECEIVE:
         CLR RI
HERE1:	 JNB RI HERE1
         MOV A,SBUF
         CLR RI
		
		 
SEND	
	 
	 
	 
	 
SEND:  MOV SBUF,A
HERE:  JNB TI,HERE
	   CLR TI
	   RET
	   
	   ORG 300H
		   DB  "We Are Ready",0
		RET
	 
	 
	 