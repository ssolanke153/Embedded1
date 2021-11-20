.INCLUDE "M32DEF.INC"

.ORG $0
  
    rjmp start

	start:
	here:      LDI r16,$20
		  LDI r17,$25
		  LDS R0,0X017

		  LDS R1,0x16
		  ADD R1,R0

		  ADD R16, $52

		  rjmp here

		.EXIT