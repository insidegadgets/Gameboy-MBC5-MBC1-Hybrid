; Multi-Game Cart Loader
; Version: 1.2
; Author: Alex from insideGadgets (www.insidegadgets.com)
; Created: 25/08/2018
; Last Modified: 20/09/2018
  
 .globl _multibankswitch
	_multibankswitch:

	LDA  HL,2(SP)

	LD   E,(HL)
	INC  HL

	LD   D,(HL)
	INC  HL
	
	
	; Load 0x7000 with MBC type (0x63, 64, 65) to unlock multi-game mode
	LD		a,D
	LD		(0x7000), a
	NOP
	NOP
	NOP
	
	; Load 0x6000 with bank value
	LD		a,E
	LD		(0x6000), a
	
	; By this time the GB should have reset
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP

   RET