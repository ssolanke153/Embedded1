ORG 00H
	LJMP MAIN
	
	
	ORG 000BH
		CPL P1.2
		RETI
		
		ORG 0030H
			MOV TMOD,#20H
			
MAIN:		MOV TH0,#0B6H
			MOV IE,#82H
			SETB TR0
			
BACK:		MOV P0,#"Y"
			MOV P2,#"N"
			
			SJMP BACK
			END