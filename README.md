# sm64-replay-rom-maker-v2
Uses Eddio0141's SM64 Replay Romhack to turn an m64 movie file into a z64 ROM that plays the movie back.

## Usage
```
replay_rom_maker.exe [your_movie.m64] [your_rom_name.z64 | -]
```
Before you can create any Replay ROMs, you must apply the .ips patches to unmodified Super Mario 64 U and J ROMs respectively, and place them into the same folder as the `replay_rom_maker.exe` executable. Make sure the ROM names match their respective patch names. Patching can be done with [Floating IPS (flips)](https://github.com/Alcaro/Flips). You are free to delete the .ips patch files after doing so.

You have two options for selecting an m64 to make into a ROM. You can either place your m64 in the same directory as the executable, rename it to `input.m64`, and run the `replay_rom_maker.exe` executable, or you can run the executable from the command line with your m64 as an argument (the argument can also be a path to an m64 not in the current directory).

You have three options for the name of the output ROM. If only an m64 is passed as an argument (ex: `replay_rom_maker.exe your_movie.m64`), the output ROM will be named `output.z64` (note: any previous `output.z64` ROM will be overwritten if you create another ROM with this name). If an m64 and a z64 name are passed as arguments (ex: `replay_rom_maker.exe your_movie.m64 your_rom_name.z64`), the output ROM will be named whatever name you passed as an argument. Finally, if an m64 and `-` are passed as arguments (ex: `replay_rom_maker.exe your_movie.m64 -`), the output ROM will have the same name as the input m64.

If no arguments are passed (`replay_rom_maker.exe`), `input.z64` and `output.z64` will be chosen by default. Pass `-h` as the only argument to see the usage again (`replay_rom_maker.exe -h`).

## Building
Simply compile it on the command line with your C compiler of choice (`gcc main.c -o replay_rom_maker.exe`, for example).
