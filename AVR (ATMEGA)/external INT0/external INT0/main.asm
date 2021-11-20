;
; external INT0.asm
;
; Created: 23-05-2020 09:14:41
; Author : Shri
;


 .include "m32def.inc"

 .org 0
 jmp main

 .org 0x02
 jmp ex0


 main:ldi r20,high(ramend)
      out sph,r20
	  ldi r20,low(ramend)
	  out spl,r20

	  sbi ddrc,3
	  sbi portd,2
	  ldi r20,1<<int0
	  out gicr,r20
	  sei

here: jmp here

ex0:
      in r21,pinc
	  ldi r22,0x08
	  eor r21,r22
	  out portc,r21

	  /*in r21,pinc
	  ldi r22,0x08
	  eor r21,r22
	  out portc,r21*/
	  reti


	  .exit
