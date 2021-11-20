; ORG 00H 
;	 MOV TMOD,#52H
;	 HERE:	 MOV TL0,#0FH
;	 MOV TH0,#0FFH 
;	 CPL P1.5
;	 ACALL DELAY 
;	 SJMP HERE
;	 DELAY:
;	 SETB TR0
;AGAIN:	JNB TF0,AGAIN
;	 
;	 CLR TR0 
;	 CLR TF0
;	 RET
;	 
;	 END

;ORG 00H 
;	MOV R0,#7
;	H1:	MOV TMOD,#10H
;BACK: MOV TL1,#00H 
;	MOV TH1,#00H
;	MOV P1,#00H
;	ACALL DELAY 
;	DJNZ R0,H1
;	H2:MOV TL1,#00H
;    MOV TH1 ,#00H
;    MOV P1,#0FFH
;    ACALL DELAY
;	DJNZ R0,H2
;     SJMP BACK

;DELAY:
;      SETB TR1
;AGAIN:JNB TF1,AGAIN
;	  CLR TR1
;	  CLR TF1
;	  RET
;	  END
	
	    ORG 00H
REPEAT:	MOV R0,#14
		MOV TMOD,#10H
H1:	    MOV TL1,#00H
		MOV TH1,#00H
		MOV P1,#01H
		ACALL DELAY 
		DJNZ R0,H1
H2:     MOV TL1,#00H
		MOV TH1,#00H
		MOV P1,#00H
		ACALL DELAY
		DJNZ R0,H2
		SJMP REPEAT
		
		
		
DELAY:
      SETB TR1
AGAIN:JNB TF1,AGAIN
	  CLR TR1
	  CLR TF1
	  RET
	  
	  END
	