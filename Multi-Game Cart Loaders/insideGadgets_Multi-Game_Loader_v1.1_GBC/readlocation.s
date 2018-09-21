; Multi-Game Cart Loader
; Version: 1.0
; Author: Alex from insideGadgets (www.insidegadgets.com)
; Created: 25/08/2018
; Last Modified: 28/08/2018

 .globl _readlocation
	_readlocation: 
	
	LDA	HL,2(SP)

	LD		E,(HL) 
	INC	HL

	LD		D,(HL)
	INC	HL
	
	
	; Load byte location to load in HL
	LD		H,D
	LD		L,E
	
	; Read location data
	LD		E,(HL)
	LD		D,#0
	
	RET