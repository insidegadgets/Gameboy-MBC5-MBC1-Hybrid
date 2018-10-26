; Multi-Game Cart Loader
; Version: 1.3
; Author: Alex from insideGadgets (www.insidegadgets.com)
; Created: 25/08/2018
; Last Modified: 5/10/2018
  
 .globl _multibankswitch
	_multibankswitch:

	LDA  HL,2(SP)

	LD   E,(HL)
	INC  HL

	LD   D,(HL)
	INC  HL
	
	
	
	; Load A with MBC type (0x63, 64, 65) to unlock multi-game mode
	LD		a,#0x3E
	LD		(0xFFAC),a
	LD		a,D
	LD		(0xFFAD),a
	
	; Load 0x7000 with A
	LD		a,#0xEA
	LD		(0xFFAE),a
	LD		a,#0x00
	LD		(0xFFAF),a
	LD		a,#0x70
	LD		(0xFFB0),a
	
	; NOPs
	LD		a,#0x00
	LD		(0xFFB1),a
	LD		a,#0x00
	LD		(0xFFB2),a
	LD		a,#0x00
	LD		(0xFFB3),a
	LD		a,#0x00
	LD		(0xFFB4),a
	
	
	; Load bank value to A
	LD		a,#0x3E
	LD		(0xFFB5),a
	LD		a,E
	LD		(0xFFB6),a
	
	; Load 0x6000 with A
	LD		a,#0xEA
	LD		(0xFFB7),a
	LD		a,#0x00
	LD		(0xFFB8),a
	LD		a,#0x60
	LD		(0xFFB9),a
	
	; NOPs
	LD		a,#0x00
	LD		(0xFFBA),a
	LD		a,#0x00
	LD		(0xFFBB),a
	LD		a,#0x00
	LD		(0xFFBC),a
	LD		a,#0x00
	LD		(0xFFBD),a
	
	
	; Load any value to A
	LD		a,#0x3E
	LD		(0xFFBE),a
	LD		a,#00
	LD		(0xFFBF),a
	
	; Load 0x5000 with A
	LD		a,#0xEA
	LD		(0xFFC0),a
	LD		a,#0x00
	LD		(0xFFC1),a
	LD		a,#0x50
	LD		(0xFFC2),a
	
	; NOPs, By this time the GB should have reset
	LD		a,#0x00
	LD		(0xFFC3),a
	LD		a,#0x00
	LD		(0xFFC4),a
	LD		a,#0x00
	LD		(0xFFC5),a
	LD		a,#0x00
	LD		(0xFFC6),a
	
	
	; Jump to HRAM and execute the above
	JP 	0xFFAC

   RET