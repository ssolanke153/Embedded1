/* 1. Observe the following noting the role of the OV flag.
*/

ORG 00H
	MOV A,#-128
	MOV R4,#-2
	ADD A,R4
	END