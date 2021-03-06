; Q1. ASSUMING THAT XTAL = 11.0592 MHz FOR THE FOLLOWING  FRQUENCY USED BY THE TIMER 1 TO SET THE BAUD RATE, AND (C) FIND THE BAUD RATE OF THE DATA TRANSFER.

;	ORG 00H
;		MOV A,PCON
;		SETB ACC.7
;		MOV  PCON,A
;		
;		MOV TMOD,#20H
;		MOV TH1,#-3
;		
;		MOV SCON,#50H
;		SETB TR1
;		MOV A,#'B'
;		A_1:	CLR TI
;		MOV SBUF,A
;		H_1:	JNB TI,H_1
;		SJMP A_1

;	END



; Q2.PORT 0 OF AN 8051 IS USED TO MONITOR A PARAMETER IN AN INDUSTRIES ENVIRONMENT. IF THE PARAMETER GIVES A READING ABOVE 0FH A MESSAGE 'H1' IS TO BE SENT
;SERIALLY.OTHERWISE,A MESSAGE 'OK' IS TO BE SENT. THE WORDS 'H1' AND 'OK' ARE BURNED INTO ROM LOCATIONS 

ORG 00H
		MOV P0,#0FFH
		MOV TMOD,#20H
		MOV TH1,#-3
		MOV SCON,#50H
		SETB TR1
	
CHECK:	MOV A,P0
		CJNE A,#0FH,TEST
		SJMP OK
	
TEST:	JNC H1
OK:	    MOV DPTR,#00A0H
		ACALL ACCESS
		SJMP CHECK
		
H1:     MOV DPTR,#0090H
		ACALL ACCESS
		SJMP CHECK

ACCESS: CLR A
		MOVC A,@A+DPTR
		ACALL SEND 
		INC DPTR
		CLR A
		MOVC A,@A+DPTR
		ACALL SEND

RET

SEND:   MOV SBUF,A
HERE:   JNB TI,HERE
        CLR TI
RET

ORG 0090H
MES1:   DB "HI"
		
ORG 00A0H
MES2:   DB "OK"
				
END
		
	
;	
;	ORG 00H
;		MOV TMOD ,20H
;		MOV TH1,#-3
;		MOV SCON,#50H
;		SETB TR1
;		
;AGAIN:	MOV A,#"A"
;		MOV SBUF,A
;		
;RPT:	JNB T1,RPT
;		CLR TI
;		SJMP AGAIN

ORG 00H
		MOV A,PCON
		MOV ACC.7,#1
		MOV PCON,A

		MOV TMOD,#20H
		MOV TH1,#-3
		MOV SCON,#50H
		SETB TR1

AGAIN:  MOV A,#"f"
        MOV SBUF,A

HERE:   JNB TI,HERE
        CLR TI
	    SJMP AGAIN