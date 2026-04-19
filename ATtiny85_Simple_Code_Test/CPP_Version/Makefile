# Makefile for ATtiny85 Christmas Song (C++ Version)

# Compiler
CXX = avr-g++

# MCU and Clock Speed
MCU = attiny85
F_CPU = 8000000UL

# Compiler flags
CXXFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os

# Source and Header files
SRC = Christmas_song.cpp
HEADERS = notes.hpp

# Output file names
ELF = Christmas_song.elf
HEX = Christmas_song.hex

# Programmer settings
PROGRAMMER = avrisp
PORT = /dev/ttyACM0 # Change this to your actual port (e.g., COM3 on Windows)
BAUD = 19200

# Default target
all: $(HEX)

# Rule to create the HEX file from the ELF file
$(HEX): $(ELF)
	avr-objcopy -O ihex -R .eeprom $< $@

# Rule to create the ELF file from the source and header files
$(ELF): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $<

# Rule to upload the HEX file to the ATtiny85
upload: $(HEX)
	avrdude -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(HEX)

# Rule to clean up all generated build files
clean:
	rm -f $(ELF) $(HEX)

.PHONY: all upload clean