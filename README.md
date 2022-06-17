# sm64-replay-rom-maker
Uses Eddio0141's SM64 Replay Romhack to turn an m64 into a z64 ROM that plays the m64.

## Usage
Before you can create any Replay ROMs, you must apply the .ips patches to unmodified Super Mario 64 U and/or J ROMs. Make sure the ROM names match the respective patch names.

You have two options for selecting an m64 to make into a ROM. You can either rename your m64 to `input.m64` and simply run the `replay_rom_maker.exe` executable, or you can run the executable from the command line with your m64 as an argument (the argument can also be a path to an m64 not in the current directory):
```
replay_rom_maker.exe my_tas.m64
```
