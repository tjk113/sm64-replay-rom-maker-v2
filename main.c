#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	FILE *m64;
	FILE *base_rom;
	FILE *output_rom;
	
	// 4 bytes is the size of the number of frames and also the size of each controller poll
	unsigned char buffer[4];
	// Address to start writing m64 data
	int addr;
	// Buffer for which ROM version to choose
	char ver[18];
	// Bool to designate whether the argument on the command line is an m64 or an output ROM name
	_Bool rom_name_only = 0;

	if (argc > 1) {
		// '-h' flag to show usage
		if (argv[1][0] == '-') {
			printf("Usage:\n	replay_rom_maker.exe [your_movie.m64] [your_rom_name.z64 | -]");
			return 0;
		}
		// Check command line for m64 name, otherwise default to input.m64
		else {
			// Check if the third-to-last char in the last element of the
			// argv array is an 'm' (we're checking if it's an m64 or z64)
			if (argv[1][strlen((const char*)argv[1]) - 3] == 'm') {
				m64 = fopen(argv[1], "rb");
			}
			else {
				printf("No m64 argument... using input.m64\n");
				m64 = fopen("input.m64", "rb");
				rom_name_only = 1;
			}
		}
	}
	else {
		printf("No m64 argument... using input.m64\n");
		m64 = fopen("input.m64", "rb");
	}

	if (m64 == NULL) {
		printf("input.m64 not found in folder");
		return 1;
	}

	// Check command line for output ROM name or '-' flag, otherwise default to output.z64
	if (argc > 2) {
		if (argv[2][0] == '-') {
			// safe to change argv[1] here after m64 already fopened its previous value?
			argv[1][strlen((const char*)argv[1]) - 3] = 'z';
			output_rom = fopen(argv[1], "wb+");
		}
		else {
			output_rom = fopen(argv[2], "wb+");
		}
	}
	else if (rom_name_only) {
		output_rom = fopen(argv[1], "wb+");
	}
	else {
		printf("No z64 argument... using output.z64\n");
		output_rom = fopen("output.z64", "wb+");
	}

	// Check m64 version (US or JP)
	fseek(m64, 0xE8, SEEK_SET);
	fread(buffer, 4, 1, m64);

	// 0xE8 should be 0x45 in a US m64
	if (buffer[0] == 0x45) {
		printf("Detected US m64\n");
		strcpy(ver, "m64_replay_us.z64");
		// 1 byte after the end of the US Replay ROM
		addr = 0x7CD000;
	} 
	else if (buffer[0] == 0x4A) {
		printf("Detected JP m64\n");
		strcpy(ver, "m64_replay_jp.z64");
		// 1 byte after the end of the JP Replay ROM
		addr = 0x762000;
	}
	else {
		printf("Unable to read m64 file");
		return 1;
	}

	base_rom = fopen(ver, "rb+");
	if (base_rom == NULL) {
		printf("%s not found in folder", ver);
		return 1;
	}

	// Copy content of base_rom to output_rom
	while (fread(buffer, 4, 1, base_rom))
		fwrite(buffer, 4, 1, output_rom);

	printf("Writing TAS...");

	// Reset m64 pointer to start and set ROM pointer to 1 byte after end of file
	fseek(m64, 0x0, SEEK_SET);
	fseek(output_rom, addr, SEEK_SET);

	printf("Done!\n");

	// Read m64 data into buffer and write buffer to ROM
	while (fread(buffer, 4, 1, m64))
		fwrite(buffer, 4, 1, output_rom);
	
	printf("Closing files...");

	fclose(m64);
	fclose(base_rom);
	fclose(output_rom);
	
	printf("Done!\n");

	// Delete EEPROM file in Mupen saves folder; otherwise the save
	// file will persist between resets of the output.z64 ROM
	// (You can uncomment this and add your own path if you'd like this functionality)
	// if (remove("D:\\1A TAS\\1A Mupen\\save\\SUPER MARIO 64       (unknown rom).eep"))
	// 	printf("Deleting .eep file from Mupen saves...Done!");
	
	return 0;
}
