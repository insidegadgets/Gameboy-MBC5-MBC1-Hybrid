/*
 Multi-Game Cart Loader
 Version: 1.1
 Author: Alex from insideGadgets (www.insidegadgets.com)
 Created: 25/08/2018
 Last Modified: 10/09/2018
 
 A loader which allows you to choose a game from a selection screen of games created with the Multi-Game Maker.
 Learn how this loader works at wwww.insidegadgets.com
 
 */

#include <stdio.h>
#include <gb/gb.h>
#include <gb/console.h>
#include <gb/drawing.h>

void init();
void checkInput();

UBYTE refreshScreen = 1;
UBYTE arrowLocation = 0;
UBYTE gamesDisplayStart = 0;
UBYTE gamesDisplayEnd = 14;

WORD letter;
UWORD bankSelect = 0;
UBYTE totalGames = 0;
UWORD readCharLocation = 0x2FFF;

WORD multibankswitch(WORD);
WORD readlocation(WORD);


void main() {
	init();
	
	printf("\n   insideGadgets\n Multi-Game Loader\n                v1.1\n");
	printf(">");
	
	// Load how many games there are
	totalGames = readlocation(readCharLocation);
	
	while(1) {
		if (refreshScreen == 1) {
			gotoxy(0,3);
			
			if (totalGames != 0xFF) {
				UBYTE g = 0;
				readCharLocation = 0x3001;
				
				readCharLocation += (UWORD) gamesDisplayStart * (UWORD) 16;
				for (g = gamesDisplayStart; g < gamesDisplayEnd; g++) {
					UBYTE x = 0;
					printf(" ");
					
					// Read file names
					for (x = 0; x < 15; x++) {
						letter = readlocation(readCharLocation);
						readCharLocation++;
						printf("%c", (UWORD) letter);
					}
					readCharLocation++; // Skip the bank select byte
					printf("\n");
				}
				
				// Arrow location
				if (arrowLocation < 14) {
					gotoxy(0,arrowLocation+3);
					printf(">");
				}
				else { // Limit arrow to bottom
					gotoxy(0,16);
					printf(">");
				}
			}
			else {
				printf("No games found");
			}
			
			refreshScreen = 0;
		}
		
		checkInput();
		wait_vbl_done();
	}
	
}

void init() {
	DISPLAY_ON;		// Turn on the display
	NR52_REG = 0x8F;	// Turn on the sound
	NR51_REG = 0x11;	// Enable the sound channels
	NR50_REG = 0x77;	// Increase the volume to its max
}

void checkInput() {
	if (joypad() & J_DOWN) {
		if (arrowLocation < totalGames-1) {
			arrowLocation++;
			refreshScreen = 1;
			if (arrowLocation >= 14) {
				gamesDisplayStart++;
				gamesDisplayEnd++;
			}
		}
	}
	if (joypad() & J_UP) {
		if (arrowLocation > 0) {
			arrowLocation--;
			refreshScreen = 1;
			
			if (arrowLocation >= 13) {
				gamesDisplayStart--;
			}
			
			if (gamesDisplayEnd > 14) {
				gamesDisplayEnd--;
			}
		}
	}
	
	if (joypad() & J_A) {
		readCharLocation = 0x3000 + ((UWORD) arrowLocation * (UWORD) 16);
		bankSelect = readlocation(readCharLocation);
		multibankswitch(bankSelect);
	}
}
