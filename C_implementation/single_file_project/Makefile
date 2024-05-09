# Makefile for AVR projects

# Compiler and flags
CC = avr-gcc
OBJCOPY = avr-objcopy
MCU = attiny85
F_CPU = 16500000UL
BAUDRATE = 19200
PORT = /dev/ttyACM0

# Compiler flags
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os
LDFLAGS =

# Source files
SRC = main.c

# Object files
OBJ = $(SRC:.c=.o)
HEX = $(SRC:.c=.hex)

# Targets
all: $(HEX)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

%.hex: %.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

flash: $(HEX)
	avrdude -c arduino -p $(MCU) -P $(PORT) -b $(BAUDRATE) -U flash:w:$<

clean:
	rm -f $(OBJ) $(HEX) *.elf

.PHONY: all flash clean

