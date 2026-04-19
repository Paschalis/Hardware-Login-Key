# Makefile for ATtiny85 Christmas Songs

# Compiler
CC = avr-gcc

# MCU and Clock Speed
MCU = attiny85
F_CPU = 8000000UL  # <-- FIX: Matched clock speed to C code (8MHz)

# Compiler flags
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os

# Source and Header files
SRC = Christmas_song.c
HEADERS = notes.h

# Object files (not strictly needed for this simple project, but good practice)
OBJ = $(SRC:.c=.o)

# ELF file
ELF = Christmas_song.elf

# HEX file
HEX = Christmas_song.hex

# Programmer settings
PROGRAMMER = avrisp
PORT = /dev/ttyACM0 # Change this to your actual port (e.g., COM3 on Windows)
BAUD = 19200

# Targets
all: $(HEX)

# Rule to create HEX from ELF
$(HEX): $(ELF)
	avr-objcopy -O ihex -R .eeprom $(ELF) $(HEX)

# Rule to create ELF from sources and headers
$(ELF): $(SRC) $(HEADERS) 
	$(CC) $(CFLAGS) -o $(ELF) $(SRC)

# Rule to upload to the ATtiny85
upload: $(HEX)
	avrdude -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(HEX)

# Rule to clean up build files
clean:
	rm -f $(ELF) $(HEX) $(OBJ)

.PHONY: all upload clean