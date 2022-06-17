#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
	FILE *m64;
	FILE *base_rom;
	FILE *output_rom;
	
	// 4 bytes is the size of the number of frames and also the size of each controller poll
	unsigned char buffer[4];
	char ver[18];
	// Address to start writing m64 data (1 byte after end of ROM)
	int us_addr = 0x7CD000;
	int jp_addr = 0x762000;
	int addr;

	// Check command line for m64 name, otherwise default to input.m64
	if (argv[1]) {
		m64 = fopen(argv[1], "rb");
	} else {
		m64 = fopen("input.m64", "rb");
	}

	output_rom = fopen("output.z64", "wb+");
	if (m64 == NULL) {
		printf("input.m64 not found in folder");
		return 1;
	}

	// Check m64 version (US or JP)
	fseek(m64, 0xE8, SEEK_SET);
	fread(buffer, 4, 1, m64);

	// 0xE8 should be 0x45 in a US ROM
	if (buffer[0] == 0x45) {
		printf("Detected US m64\n");
		strcpy(ver, "m64_replay_us.z64");
		addr = us_addr;
	} else {
		printf("Detected JP m64\n");
		strcpy(ver, "m64_replay_jp.z64");
		addr = jp_addr;
	}

	base_rom = fopen(ver, "rb+");
	if (base_rom == NULL) {
		printf("%s not found in folder", ver);
		return 1;
	}

	// Copy content of base_rom to output_rom
	while (fread(buffer, 4, 1, base_rom))
		fwrite(buffer, 4, 1, output_rom);

	// Copy data
	printf("Writing TAS...\n");

	// Reset m64 pointer to start and set ROM pointer to 1 byte after end of file
	fseek(m64, 0x0, SEEK_SET);
	fseek(output_rom, addr, SEEK_SET);

	// Read m64 data into buffer and write buffer to ROM
	while (fread(buffer, 4, 1, m64))
		fwrite(buffer, 4, 1, output_rom);
	
	// Close files
	printf("Closing files...\n");
	
	// Delete EEPROM file in Mupen saves folder; otherwise the save
	// file will persist between resets of the output.z64 ROM
	// (You can uncomment this and add your own path if you'd like this functionality)

	// if (remove("D:\\1A TAS\\1A Mupen\\save\\SUPER MARIO 64       (unknown rom).eep"))
	// 	printf("Deleting .eep file from Mupen saves...");

	fclose(m64);
	fclose(base_rom);
	fclose(output_rom);
	
	printf("Done!\n");
	
	return 0;
}
