;
; counter.asm
;
; Created: 24-05-2020 08:28:07
; Author : Shri
 

 .include "m32def.inc"
 .org 0
    jmp main
 
 .org 0x02
    jmp EX0

 
main: 
    ldi r16,high(ramend)
	out sph,r16

	ldi r16,low(ramend)
	out spl,r16

	sbi portd,2
	ldi r20,1<<int0
	out gicr,r20


	cbi DDRB,0

	 ldi r20,0xFF
	 out ddrc,r20
	 ldi r20,0x06
	 out tccr0,r20
	 sei
	 here:jmp here
 
 
      
    
  EX0:   ;in r20,tcnt0
          ldi r22,0x00
		  ldi r21,0x01
		  eor r21,r22
		   out portc,r21
		   in r16,tifr
		   in r17,pind
		   sbrs r16,tov0
		   
		   rjmp EX0

	   ldi r16,1<<tov0
	   out tifr,r16
	   
	    sbrs r17,2
	   rjmp EX0
	   ldi r20,0x00
	   out portc , r20
	   reti
	  

	   