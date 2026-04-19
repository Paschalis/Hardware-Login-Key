# Using the Makefile

Each firmware variant (`tactile_switch`, `touch_pad`) ships with its own
Makefile. All commands below must be run from inside the variant folder.

## Quick reference

| Command | What it does |
|---|---|
| `make` | Compile firmware → `main.elf` + `main.hex` |
| `make upload` | Flash `main.hex` to the ATtiny85 via Arduino-as-ISP |
| `make set-fuses` | Configure fuse bits for 16 MHz external crystal (one-time per chip) |
| `make clean` | Delete build artefacts (`*.elf`, `*.hex`) |

## Makefile variables you may need to change

Open the Makefile in your editor and adjust these at the top if needed:

```makefile
PROGRAMMER = avrisp          # programmer type (avrisp2, usbtiny, …)
PORT       = /dev/ttyACM0   # serial port (COMx on Windows, /dev/cu.* on macOS)
BAUD       = 19200           # must match ArduinoISP sketch
```

## Typical workflow

```bash
# First time only — set fuses on a fresh chip
cd C_implementation/tactile_switch
make set-fuses

# Every time you change the firmware
make
make upload
```

## Prerequisites

```bash
# Debian / Ubuntu
sudo apt-get install make gcc-avr binutils-avr avr-libc avrdude

# macOS
brew tap osx-cross/avr && brew install avr-gcc avrdude
```

[⬅ Back to README](README.md)
