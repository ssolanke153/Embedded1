; ORG 00H
;	 LJMP MAIN
;	 
;	 
;	 ORG 001BH
;		 LJMP ISR_T1
;		 
;		 ORG 0030H
;MAIN:		 MOV TMOD,#10H
;			 MOV P0,#0FFH
;			 MOV TL1,#018H
;			 MOV TH1,#0FCH
;			 MOV IE,#88H
;			 SETB TR1
;BACK:        MOV A,P0
;             MOV P1,A
;			 SJMP BACK
;			 
;ISR_T1:		 CLR TR1
;			 CLR P2.1
;			 MOV R2,#4
;HERE:		 DJNZ R2,HERE
;			 MOV TL1,#18H
;			 MOV TH1,#0FCH
;			 SETB TR1
;			 SETB P2.1
;			 RETI
;			 
;			 END
;		

ORG 00H
	LJMP MAIN
	
	ORG 000BH
		CPL P1.3
		RETI 
		
		ORG 001BH
			CPL P2.3
			RETI
			
			ORG 0030H
MAIN:		MOV TMOD,#22H
            MOV IE,#8AH
			MOV TH0,#048H
			MOV TH1,#0B6H
			SETB TR0
			SETB TR1
WAIT:       SJMP WAIT
			END
				
				
				