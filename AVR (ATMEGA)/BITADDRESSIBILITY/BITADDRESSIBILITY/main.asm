;
; BITADDRESSIBILITY.asm
;
; Created: 09-05-2020 9.58.03 AM
; Author : Shri


 
 //FLAG REGISTERS 

  // 1)  METHODS  OF SETING BITS

    BSET 0    // THIS IS SET THE CARRY FLAG
	 
	 LDI R16,1<<SREG_H   
	 OUT SREG, R16       // THIS IS SET H FLAG WE CAN ALSO SET MULTIPLE FLAG BY THIS INSTRUCTION

	 LDI R16,(1<<SREG_S)|(1<<SREG_N)|(1<<SREG_C)
	 OUT SREG,R16 

	SEC // THIS SET THE CARRY FLAG
	SEV // THIS SET THE OVERFLOW FLAG



	// 2) METHODS OF CLEARING THE FLAGS

	BCLR 0   // THIS WILL CLEAR CARRY FLAG
	 
   CLC       // THIS WILL ALSO USED TO CLEAR FLAGS
   CLV       // IT CLEARED OVERFLOW FLAG
   CLS       // IT CLEARED SIGN FLAG
   CLN       // IT CLEARED NEGATIVE FLAG


   //BRANCH INSTRUCTIONS USING FLAGS

   //1) IF FLAGS ARE SET
      
	  BRBS 0,L1  //IT WILL JUMP ON L1 IF THE C=1
	  BRCS L1    // IT JUMP ON L1 IF C=1
	  BRLO L1    // IT JUMP ON L1 IF C=1

	  BRBS 1,L1  // IT WILL JUMP ON L1 IF THE Z=1
	  BREQ L1    // IT JUMPS ON L1 IF Z=1
	  
	  BRBS 3,L1  // IT JUMP ON L1 IF V=1
	  BRVS L1    // IT JUMP ON L1 IF V=1
	   
	  BRBC 2,L1  // IT JUMP ON L1 IF N=1
	  BRMI L1    // IT JUMPS ON L1 IF N=1
	  
	  BRBC 4,L1  // IT JUMP ON L1 IF S=1
	  BRLT L1    // IT JUMPS ON L1 IF S=1

	  BRBS 5,L1  // IT JUMP ON L1 IF H=1
	  BRHS L1    // IT JUMPS ON L1 IF H=1

	  BRBS 6,L1  // IT JUMP ON L1 IF T=1
	  BRTS L1    // IT JUMPS ON L1 IF T=1

	  BRBS 7,L1  // IT JUMP ON L1 IF I=1
	  BRIE L1    // IT JUMPS ON L1 IE I=1

	  //2) IF FLAGS ARE CLR

	  BRBC 0,L1   //  IT JUMP ON L1 IF C=0
	  BRCC L1     //  IT JUMP ON L1 IF C=0
	  BRSH L1     //  IT JUMP ON L1 IF C=0

	  BRBC 3 ,L1  //  IT JUMP ON L1 IF V =0 
	  BRVC L1     //  IT JUMP ON L1 IF V=0

	  BRBC 2,L1   //  IT JUMP ON L1 IF N=0
	  BRPL L1     //  IT JUMP ON L1 IF N=0

	  BRBC 1,L1   //  IT JUMP ON L1 IF Z=0
	  BRNE L1     //  IT JUMP ON L1 IF Z=0

	  BRBC 4,L1   //  IT JUMP ON L1 IF H=0
	  BRHC L1     //  IT JUMP ON L1 IF H=0

	  BRBC 5,L1   //  IT JUMP ON L1 IF S=0
	  BRGE L1     //  IT JUMP ON L1 IF C=0

	  BRBC 6,L1   // IT JUMP ON L1 IF T=0
	  BRTC L1     // IT JUMP ON L1 IF T=0

	  BRBC 7,L1   // IT JUMP ON L1 IF I=0
	  BRID L1     // IT JUMP ON L1 IF I=0

	  

	L1:
	   NOP
	  
	   .EXIT
