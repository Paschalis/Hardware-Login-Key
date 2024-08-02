# Compiler settings
CC = avr-gcc
OBJCOPY = avr-objcopy
# ATtiny85 specific settings
MCU = attiny85
F_CPU = 16000000UL  # Adjust this if your ATtiny85 is running at a different frequency

AVRDUDE = avrdude

# Compiler flags
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -I./DigiKeyboard

LDFLAGS =



# Source files
SRC = main.c DigiKeyboard/usbdrv.c
OBJ = $(SRC:.c=.o)
HEX = main.hex

# Default target
all: $(HEX)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into .elf
main.elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

# Convert .elf to .hex
$(HEX): main.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Upload .hex file to ATtiny85 using Arduino as ISP
upload: $(HEX)
	$(AVRDUDE) -c arduino -p $(MCU) -P /dev/ttyACM0 -b 19200 -U flash:w:$<

# Clean up
clean:
	rm -f $(OBJ) main.elf main.hex

.PHONY: all upload clean
