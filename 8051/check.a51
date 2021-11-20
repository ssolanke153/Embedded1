ORG 00H
	   MOV A,#55H
	   MOV R2,#10
	   MOV R0,#90H
BACK:
	     MOV @R0,A
	     INC R0
	     DJNZ R2,BACK
	     SJMP $
		 END
			
			
			
			