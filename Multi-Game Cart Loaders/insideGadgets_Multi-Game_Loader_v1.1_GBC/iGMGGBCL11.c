/*
 Multi-Game Loader - For GBC games
 Version: 1.1
 Author: Alex from insideGadgets (www.insidegadgets.com)
 Created: 25/08/2018
 Last Modified: 15/09/2018
 
 A loader which allows you to choose a game from a selection screen of games created with the Multi-Game Maker.
 Learn how this loader works at wwww.insidegadgets.com
 
 */

#include <stdio.h>
#include <gb/gb.h>
#include <gb/console.h>
#include <gb/drawing.h>

#include "bar_c.h"
#include "bar_c.c"
#include "bar_m.c"

void checkInput();

UBYTE refreshScreen = 1;
UBYTE arrowLocation = 0;
UBYTE gamesDisplayStart = 0;
UBYTE gamesDisplayEnd = 14;

WORD letter;
UWORD bankSelect = 0;
UWORD mbcSelect = 0;
UBYTE totalGames = 0;
UWORD readCharLocation = 0x2FFF;

WORD multibankswitch(WORD);
WORD readlocation(WORD);


const UWORD bar_p[] =
{
  bar_cCGBPal0c0,bar_cCGBPal0c1,bar_cCGBPal0c2,bar_cCGBPal0c3,
  bar_cCGBPal1c0,bar_cCGBPal1c1,bar_cCGBPal1c2,bar_cCGBPal1c3,
  bar_cCGBPal2c0,bar_cCGBPal2c1,bar_cCGBPal2c2,bar_cCGBPal2c3,
  bar_cCGBPal3c0,bar_cCGBPal3c1,bar_cCGBPal3c2,bar_cCGBPal3c3,
  bar_cCGBPal4c0,bar_cCGBPal4c1,bar_cCGBPal4c2,bar_cCGBPal4c3,
  bar_cCGBPal5c0,bar_cCGBPal5c1,bar_cCGBPal5c2,bar_cCGBPal5c3,
  bar_cCGBPal6c0,bar_cCGBPal6c1,bar_cCGBPal6c2,bar_cCGBPal6c3,
  bar_cCGBPal7c0,bar_cCGBPal7c1,bar_cCGBPal7c2,bar_cCGBPal7c3
};

const unsigned char bar_a[] =
{
  7,7,4,4,4,6,6,6,2,2,2,5,5,5,1,1,1,3,3,3,
  7,7,4,4,4,6,6,6,2,2,2,5,5,5,1,1,1,3,3,3,
  7,7,4,4,4,6,6,6,2,2,2,5,5,5,1,1,1,3,3,3,
  7,7,4,4,4,6,6,6,2,2,2,5,5,5,1,1,1,3,3,3,
  7,7,4,4,4,6,6,6,2,2,2,5,5,5,1,1,1,3,3,3,
  7,7,4,4,4,6,6,6,2,2,2,5,5,5,1,1,1,3,3,3,
  7,7,4,4,4,6,6,6,2,2,2,5,5,5,1,1,1,3,3,3,
  7,7,4,4,4,6,6,6,2,2,2,5,5,5,1,1,1,3,3,3,
  7,7,4,4,4,6,6,6,2,2,2,5,5,5,1,1,1,3,3,3,
  7,7,4,4,4,6,6,6,2,2,2,5,5,5,1,1,1,3,3,3,
  7,7,4,4,4,6,6,6,2,2,2,5,5,5,1,1,1,3,3,3,
  7,7,4,4,4,6,6,6,2,2,2,5,5,5,1,1,1,3,3,3,
  7,7,4,4,4,6,6,6,2,2,2,5,5,5,1,1,1,3,3,3,
  7,7,4,4,4,6,6,6,2,2,2,5,5,5,1,1,1,3,3,3,
  3,3,0,0,0,5,5,5,0,0,0,6,6,6,0,0,0,7,7,7,
  3,3,3,3,0,0,0,0,5,5,5,5,0,0,0,0,0,0,0,0,
  3,3,3,3,0,0,0,0,5,5,5,5,0,0,0,0,0,0,0,0,
  3,3,3,3,0,0,0,0,5,5,5,5,0,0,0,0,0,0,0,0
};

int main(void)
{
	/* Transfer color palettes */
	/*set_bkg_palette( 7, 1, &bar_p[0] );
	set_bkg_palette( 6, 1, &bar_p[4] );
	set_bkg_palette( 5, 1, &bar_p[8] );
	set_bkg_palette( 4, 1, &bar_p[12] );
	set_bkg_palette( 3, 1, &bar_p[16] );
	set_bkg_palette( 2, 1, &bar_p[20] );
	set_bkg_palette( 1, 1, &bar_p[24] );
	set_bkg_palette( 0, 1, &bar_p[28] );*/
	
	set_bkg_palette( 7, 1, &bar_p[0] );
	set_bkg_palette( 6, 1, &bar_p[0] );
	set_bkg_palette( 5, 1, &bar_p[0] );
	set_bkg_palette( 4, 1, &bar_p[0] );
	set_bkg_palette( 3, 1, &bar_p[0] );
	set_bkg_palette( 2, 1, &bar_p[0] );
	set_bkg_palette( 1, 1, &bar_p[0] );
	set_bkg_palette( 0, 1, &bar_p[0] );

	// CHR code transfer
	set_bkg_data( 0x0, 32, bar_c );

	// Select VRAM bank 1 
	VBK_REG = 1;

	// Select VRAM bank 0
	VBK_REG = 0;

	SHOW_BKG;
	enable_interrupts();
	DISPLAY_ON;
	

	printf("\n   insideGadgets\n Multi-Game Loader\n                v1.0\n");
	printf(">");

	// Load how many games there are
	totalGames = readlocation(readCharLocation);
	//totalGames = 5;

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
					//for (x = 0; x < 14; x++) {
					for (x = 0; x < 15; x++) {
						letter = readlocation(readCharLocation);
						readCharLocation++;
						printf("%c", (UWORD) letter);
					}
					//readCharLocation += 2; // Skip the bank select byte
					readCharLocation++;
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
	}
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
		mbcSelect = readlocation(readCharLocation+1);
		multibankswitch(mbcSelect << 8 | bankSelect);
	}
}
