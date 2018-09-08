Gameboy MBC5/MBC1 Hybrid
Author: Alex from insideGadgets (www.insidegadgets.com)
Created: 18/04/2018
Last Modified: 8/09/2018
License: CC-BY


Check out the different firmware releases to see what differences they offer:

2MB ROM, 128KB SRAM Cart
------------------------
Firmware R1:
MBC1 support is limited to 512KB ROM / 8 KBytes RAM, it’s locked in “ROM Banking Mode” but without the 2MB ROM support.

Firmware R1.1:
MBC1 support now allows for ROM banking mode to 2MB but for RAM banking mode it's locked to 8KB RAM.

Firmware R2:
Allows this cart to be a Multi-Game Cart when you run our loader software (Multi-Game Cart Maker v1.0), drag & drop your ROM files to the executable, then write the output ROM file to the cart. It consumes 20mA more than R1 and about 10-20% of games run through the Multi-Game loader may not work. You can still run the cart as a regular Flash cart but once again it will consume 20mA more.
MBC1 support is limited to 512KB ROM / 8 KBytes RAM, it’s locked in “ROM Banking Mode” but without the 2MB ROM support.


2MB ROM, 32KB FRAM Cart
------------------------
Firmware R1:
MBC1 support is limited to 512KB ROM / 8 KBytes RAM, it’s locked in “ROM Banking Mode” but without the 2MB ROM support.



Note: Having some MBC1 support may break a few MBC5 games.
Our MBC5 implementation differs from the standard, switching to bank 0 gives bank 1 like in MBC1/3.


CPLD: EPM3064ATC44-10N
Programmer: Altera USB Blaster Rev. c (from Ebay)
Programmed using: Quartus II 13.0sp1 (64-bit) Web Edition
Simulation: ModelSim-Altera 10.1d (Quartus II 13.0sp1)