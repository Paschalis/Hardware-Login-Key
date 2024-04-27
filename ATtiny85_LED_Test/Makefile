# Makefile for ATtiny85 LED Blinking

# Compiler
CC = avr-gcc

# Compiler flags
CFLAGS = -mmcu=attiny85 -DF_CPU=1000000UL -Os

# Source files
SRC = Christmas_song.c

# Object files
OBJ = $(SRC:.c=.o)

# ELF file
ELF = Christmas_song.elf

# HEX file
HEX = Christmas_song.hex

# Programmer settings
PROGRAMMER = avrisp
PORT = /dev/ttyACM0
BAUD = 19200

# Targets
all: $(HEX)

$(HEX): $(ELF)
	avr-objcopy -O ihex -R .eeprom $(ELF) $(HEX)

$(ELF): $(SRC)
	$(CC) $(CFLAGS) -o $(ELF) $(SRC)

upload: $(HEX)
	avrdude -c $(PROGRAMMER) -p attiny85 -P $(PORT) -b $(BAUD) -U flash:w:$(HEX)

clean:
	rm -f $(ELF) $(HEX) $(OBJ)

.PHONY: all upload clean
