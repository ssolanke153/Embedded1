ORG 00H 
 LJMP MAIN
 
 ORG 0030H
	 MAIN:SETB TCON.0
	 MOV IE,#81H
	 HERE: SJMP HERE
	 
	 
	 ORG 0003H
		 LJMP TEST 
		 ORG 0080H
			 TEST:SETB P0.1
			 SETB P0.2
			 SETB C
			 TEST1: MOV C,P0.1
			 JNC SW1
			 MOV C,P0.2
			 JNC SW2
			 MOV A,#0FFH
			  
			 RETI
			 
			 SW1:MOV C,P0.2
			 JNC BOTH
			 MOV A,#01H
			 
			 SJMP TEST1
			 SW2:MOV A,#02H
			 
			 SJMP TEST1
			 BOTH: MOV A,#0FH
			  
			 SJMP TEST1	  
RET					 
END

