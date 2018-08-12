Gameboy MBC5/MBC1 Hybrid
Author: Alex from insideGadgets (www.insidegadgets.com)
Created: 18/04/2018
Last Modified: 6/08/2018
License: CC-BY

CPLD: EPM3064ATC44-10N
Programmer: Altera USB Blaster Rev. c (from Ebay)
Programmed using: Quartus II 13.0sp1 (64-bit) Web Edition
Simulation: ModelSim-Altera 10.1d (Quartus II 13.0sp1)


Note: Having some MBC1 support may break a few MBC5 games.
Our MBC5 implementation differs from the standard, switching to bank 0 gives bank 1 like in MBC1/3.
Our MBC1 support is limited to 512KB ROM / 8 KBytes RAM, it’s locked in “ROM Banking Mode” but without the 2MB ROM support.
