/*
 Multi-Game Cart Maker
 Version: 1.1
 Author: Alex from insideGadgets (www.insidegadgets.com)
 Created: 25/08/2018
 Last Modified: 10/09/2018
 
 Drag and drop your ROM files all at once to this executable and it will create an output.gb file for you to flash to the  
 insideGadgets Gameboy 2MB 128KB SRAM Flash Cart running Firmware R2 (not the default).
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

// Read one letter from stdin
char read_one_letter (void) {
	char c = getchar();
	while (getchar() != '\n' && getchar() != EOF);
	return c;
}

int main(int argc, char **argv) {
	
	printf("insideGadgets - Multi-Game Cart Maker v1.1\n");
	printf("##################################################\n");
	printf("This only works with the insideGadgets Gameboy 2MB 128KB SRAM Flash Cart \nrunning Firmware R2 (not the default). \n\n");
	
	uint8_t buffer[16] = {0x00};
	uint8_t romBank = 2;
	
	if (argc >= 2) {
		// Calculate file sizes
		long fileSizeTotal = 32768; // Loader size
		for (uint8_t g = 1; g < argc; g++) {
			FILE *romReadFile = fopen(argv[g], "rb");
			fseek (romReadFile, 0, SEEK_END);
			long fileSize = ftell (romReadFile);
			fileSizeTotal += fileSize;
			fclose(romReadFile);
		}
		
		// Check if too large
		if (fileSizeTotal >= 2097152) {
			printf("ROM file too large, more than 2MB: %i\n", fileSizeTotal);
			read_one_letter();
			return 0;
		}
		
		// Copy the base rom file to the output file
		system("copy base.gb output.gb > /nul");
		
		FILE *romWriteFile = fopen("output.gb", "ab");
		
		// Write how many games there are
		uint8_t gamesCount = argc;
		buffer[0] = gamesCount - 1;
		fwrite(buffer, 1, 1, romWriteFile);
		
		// Write the game names
		for (uint8_t g = 1; g < gamesCount; g++) {
			// Read ROM game title
			uint16_t startLocation = 0x0134;
			uint8_t gameTitle[16];
			FILE *romReadFile = fopen(argv[g], "rb");
			fseek(romReadFile, startLocation, SEEK_SET);
			fread(buffer, 1, 15, romReadFile);
			
			// File size
			fseek (romReadFile, 0, SEEK_END);
			long fileSize = ftell (romReadFile);
			fclose(romReadFile);
			
			// Parse game title
			for (uint8_t x = 0; x < 15; x++) {
				if ((buffer[x] >= 0x30 && buffer[x] <= 0x39) || // 0-9
					 (buffer[x] >= 0x41 && buffer[x] <= 0x5A) || // A-Z
					 (buffer[x] >= 0x61 && buffer[x] <= 0x7A) || // a-z
					 (buffer[x] >= 0x24 && buffer[x] <= 0x29) || // #$%&'()
					 (buffer[x] == 0x2E) || // .
					 (buffer[x] == 0x5F) || // _
					 (buffer[x] == 0x20)) { // Space
					gameTitle[x] = buffer[x];
				}
				// Replace with an underscore
				else if (buffer[x] == 0x3A) { // :
					gameTitle[x] = '_';
				}
				else {
					gameTitle[x] = 0;
				}
			}
			gameTitle[15] = 0;
			
			printf("Adding: %s\n", gameTitle);
			
			// Write ROM bank up to
			buffer[0] = romBank;
			fwrite(buffer, 1, 1, romWriteFile);
			
			// Write the game title
			fwrite(gameTitle, 1, 15, romWriteFile);
			
			// Calculate ROM banks used
			romBank += fileSize / 16384;
		}
		
		// Write FF's to make 0x7FFF
		uint16_t remainingFFs = (0x4FFF - ((gamesCount - 1) * 16)) / 16;
		for (uint8_t x = 0; x < 16; x++) {
			buffer[x] = 0xFF;
		}
		for (uint16_t x = 0; x <= remainingFFs; x++) {
			fwrite(buffer, 1, 16, romWriteFile);
		}
		fclose(romWriteFile);
		
		// Append the ROM files
		for (uint8_t g = 1; g < gamesCount; g++) {
			char appendCommand[255];
			strncpy(appendCommand, "copy /b output.gb+\"", 21);
			strncat(appendCommand, argv[g], 200);
			strncat(appendCommand, "\" output.gb", 12);
			strncat(appendCommand, " > /nul", 8);
			
			system(appendCommand);
		}
		
		printf("Total file size: %i\n", fileSizeTotal);
		printf("\nCompleted, press any key\n");
	}
	else {
		printf("You need to drag and drop your ROM files to this executable\n");
	}
	
	read_one_letter();
	
	return 0;
}