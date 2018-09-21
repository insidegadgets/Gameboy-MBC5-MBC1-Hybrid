; Multi-Game Cart Loader
; Version: 1.0
; Author: Alex from insideGadgets (www.insidegadgets.com)
; Created: 25/08/2018
; Last Modified: 28/08/2018
  
 .globl _multibankswitch
	_multibankswitch:

	LDA  HL,2(SP)

	LD   E,(HL)
	INC  HL

	LD   D,(HL)
	INC  HL
	
	
	; **************************************
	; Load HRAM with commands to run (start)
	; **************************************
	
	; Load A with 0x65
	LD		a,#0x3E
	LD		(0xFFAC),a
	LD		a,#0x65
	LD		(0xFFAD),a
	
	; Load 0x7000 with A to unlock multi-game mode
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
	
	
	; Reset registers to defaults
	LD		a,#0x3E
	LD		(0xFFBE),a
	LD		a,#0x00
	LD		(0xFFBF),a
	LD		a,#0x47
	LD		(0xFFC0),a
	
	LD		a,#0x3E
	LD		(0xFFC1),a
	LD		a,#0x13
	LD		(0xFFC2),a
	LD		a,#0x4F
	LD		(0xFFC3),a

	LD		a,#0x3E
	LD		(0xFFC4),a
	LD		a,#0x00
	LD		(0xFFC5),a
	LD		a,#0x57
	LD		(0xFFC6),a

	LD		a,#0x3E
	LD		(0xFFC7),a
	LD		a,#0xD8
	LD		(0xFFC8),a
	LD		a,#0x5F
	LD		(0xFFC9),a
	
	LD		a,#0x21
	LD		(0xFFCA),a
	LD		a,#0x4D
	LD		(0xFFCB),a
	LD		a,#0x01
	LD		(0xFFCC),a
	
	LD		a,#0x31
	LD		(0xFFCD),a
	LD		a,#0xFE
	LD		(0xFFCE),a
	LD		a,#0xFF
	LD		(0xFFCF),a
	
	LD		a,#0x3E
	LD		(0xFFD0),a
	LD		a,#0x11
	LD		(0xFFD1),a
	
	
	; JP 0x100
	LD		a,#0xC3
	LD		(0xFFD2),a
	LD		a,#0x00
	LD		(0xFFD3),a
	LD		a,#0x01
	LD		(0xFFD4),a
	
	
	; ************************************
	; Load HRAM with commands to run (end)
	; ************************************
	
	
	; Clear I/O to default (no need to load these in HRAM)
	LD		a, #0x00
	LD		(0xFF07),a
	LD		a, #0xBF
	LD		(0xFF11),a
	LD		a, #0xF3
	LD		(0xFF12),a
	LD		(0xFF25),a	
	LD		a, #0x91
	LD		(0xFF40),a
	LD		a, #0xFC
	LD		(0xFF47),a
	LD		a, #0xFF
	LD		(0xFF48),a
	LD		(0xFF49),a	
	LD		a, #0x00
	LD		(0xFFFF),a
	
	
	; Jump to HRAM and execute the above
	JP 	0xFFAC

   RET