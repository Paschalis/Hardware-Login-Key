# Instructions for Testing Christmas Song Code Testing LED Blinking on ATtiny85

This folder contains the code `Christmas_song.c` to play a Christmas song on an ATtiny85 microcontroller.

## Requirements
- ATtiny85 microcontroller
- Arduino Uno or another AVR programmer
- Linux environment with avr-gcc, avr-objcopy, and avrdude installed
- LED and appropriate resistor for testing

## Option 1 (Using terminal)

### Steps
1. Compile the code to generate the ELF file:
    ```bash
    avr-gcc -mmcu=attiny85 -DF_CPU=1000000UL -Os -o Christmas_song.elf Christmas_song.c
    ```

2. Convert the ELF file to a HEX file:
    ```bash
    avr-objcopy -O ihex -R .eeprom Christmas_song.elf Christmas_song.hex
    ```

3. Set permissions for the programming port (e.g., `/dev/ttyACM0`):
    ```bash
    sudo chmod a+rw /dev/ttyACM0
    ```

4. Upload the HEX file to the ATtiny85 using avrdude and an AVR programmer (e.g., Arduino Uno):
    ```bash
    avrdude -c avrisp -p attiny85 -P /dev/ttyACM0 -b 19200 -U flash:w:Christmas_song.hex
    ```

5. Once uploaded, listen for the Christmas song played by the ATtiny85.

If everything is set up correctly, you should see the LED connected to the ATtiny85 blinking in sync with the Christmas song playing from the ATtiny85.

## Option 2 (Using the Makefile)

To simplify the process of compiling and uploading the code to the ATtiny85, you can use the provided Makefile. Follow these steps:

1. Open a terminal window.

2. Navigate to the directory containing your code (`Christmas_song.c`) and the Makefile.

3. Type the following command to compile your code and generate the HEX file:
   ```bash
   make
4. Type the following command to upload the HEX file to the ATtiny85:
   ```bash
    make upload 
5. Running the following command:
    ```bash
    make clean 
    ```
    removes the ELF file (Christmas_song.elf), the HEX file (Christmas_song.hex), and any object files generated during compilation (*.o) from your project directory, leaving it in a clean state.

## Notes
- Ensure that the wiring between the Arduino Uno and the ATtiny85 is correct before uploading the code.
- Adjust the permissions and port name (`/dev/ttyACM0`) as necessary depending on your system configuration.
