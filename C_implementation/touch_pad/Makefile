# Makefile for ATtiny85 V-USB Hardware Key

# Compiler
CC = avr-gcc

# MCU and Clock Speed
MCU = attiny85
F_CPU = 16000000UL # IMPORTANT: Must match usbconfig.h

# Source files
SRC = main.c usbdrv/usbdrv.c usbdrv/usbdrvasm.S
# Note: oddebug.c is not included to save space

# Output file name
ELF = main.elf
HEX = main.hex

# Compiler flags
CFLAGS = -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU)

# Programmer settings (change as needed)
PROGRAMMER = avrisp
PORT = /dev/ttyACM0
BAUD = 19200

# Default target
all: $(HEX)

# Rule to create HEX from ELF
$(HEX): $(ELF)
	avr-objcopy -O ihex -R .eeprom $< $@

# Rule to create ELF from sources
$(ELF): $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC)

# Rule to upload HEX to ATtiny85
upload: $(HEX)
	avrdude -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(HEX)

# Rule to set fuses for 16MHz external crystal (RUN THIS ONCE PER CHIP)
set-fuses:
	avrdude -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U lfuse:w:0xFF:m -U hfuse:w:0xDD:m

# Rule to clean up build files
clean:
	rm -f $(ELF) $(HEX)

.PHONY: all upload clean set-fuses