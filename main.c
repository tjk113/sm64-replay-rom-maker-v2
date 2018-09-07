#include <stdio.h>
#include <unistd.h>

int main () {
	FILE *m64;
	FILE *rom;
	
	// 4 bytes is the size of the number of frames and also the size of each controller poll
	char buffer[4];
	
	// Initialize files
	printf("Opening files...\n");
	
	m64 = fopen("input.m64", "r");
	rom = fopen("output.z64", "r+");
	
	if (m64 == NULL || rom == NULL)
		return 1;
	
	// Read the number of frames
	printf("Writing metadata...\n");
	
	fseek(m64, 0x018, SEEK_SET);
	fread(buffer, 1, 4, m64);
	
	// Write to ROM, but reverse endianness
	fseek(rom, 0x7CC770, SEEK_SET);
	
	for (int i = 3; i > -1; i --) {
		fwrite(&buffer[i], 1, 1, rom);
	}
	
	// Put M64 pointer at start of controller data
	fseek(m64, 0x400, SEEK_SET);
	
	// Copy data
	printf("Writing TAS...\n");
	
	while (fread(buffer, 1, 4, m64))
		fwrite(buffer, 1, 4, rom);
	
	// Clear the rest of the ROM
	ftruncate(fileno(rom), ftell(rom));
	
	// Close files
	printf("Closing files...\n");
	fclose(m64);
	fclose(rom);
	
	printf("Done!\n");
	
	return 0;
}
