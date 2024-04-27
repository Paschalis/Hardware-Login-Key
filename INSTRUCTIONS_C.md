# Programming ATtiny85 Instructions (C)

## Option 1: Micronucleus Bootloader

1. **Download Micronucleus**: Visit the [Micronucleus GitHub repository](https://github.com/micronucleus/micronucleus) and download the bootloader software appropriate for your operating system.

2. **Compile Your Code**: Compile your code into a `.hex` file using `avr-gcc` and `avr-objcopy`. For example:

    ```bash
    avr-gcc -mmcu=attiny85 -Os -o main.elf main.c
    avr-objcopy -O ihex -R .eeprom main.elf main.hex
    ```

3. **Connect ATtiny85**: Connect your ATtiny85 to your computer using a USB cable. Ensure that the USB pads are connected properly.

4. **Enter Bootloader Mode**: Press the reset button on your ATtiny85 board to enter bootloader mode. This might involve holding down a button or connecting specific pins.

5. **Upload `.hex` File**: Use the Micronucleus bootloader software to upload the `.hex` file to the ATtiny85. Follow the instructions provided with the software for uploading the file.

6. **Verify Upload**: After uploading the `.hex` file, verify that the programming was successful. The Micronucleus software may provide feedback or confirmation messages.

7. **Reset ATtiny85**: Once the upload is complete, reset the ATtiny85 by disconnecting and reconnecting power, or following the instructions provided by the Micronucleus software.

8. **Run Program**: After resetting the ATtiny85, it should execute your program.

## Option 2: AVRISP

1. **Connect AVRISP**: Connect your AVRISP programmer to your computer and to the ATtiny85. Ensure that the connections are correct (MISO, MOSI, SCK, RESET, VCC, and GND).

2. **Compile Your Code**: Compile your code into a `.hex` file using `avr-gcc` and `avr-objcopy`. For example:

    ```bash
    avr-gcc -mmcu=attiny85 -Os -o main.elf main.c
    avr-objcopy -O ihex -R .eeprom main.elf main.hex
    ```

3. **Upload `.hex` File**: Use AVRDUDE or a similar programming tool to upload the `.hex` file to the ATtiny85. For example:

    ```bash
    avrdude -c avrisp2 -p attiny85 -U flash:w:main.hex
    ```

4. **Verify Upload**: After uploading the `.hex` file, verify that the programming was successful. AVRDUDE may provide feedback or confirmation messages.

5. **Reset ATtiny85**: Once the upload is complete, reset the ATtiny85 by power-cycling it or using the RESET pin.

6. **Run Program**: After resetting the ATtiny85, it should execute your program.

## Option 3: Arduino as ISP

1. **Prepare Arduino Uno**: Upload the ArduinoISP sketch to your Arduino Uno board using the Arduino IDE. This sketch turns the Arduino Uno into an ISP programmer.

2. **Connect Arduino Uno as ISP**: Connect your Arduino Uno to your computer via USB. Then, connect the following pins from the Arduino Uno to the ATtiny85:
    - Arduino Uno **5V** pin to ATtiny85 **VCC** pin
    - Arduino Uno **GND** pin to ATtiny85 **GND** pin
    - Arduino Uno **Pin 10** (SS) to ATtiny85 **RESET** pin
    - Arduino Uno **Pin 11** (MOSI) to ATtiny85 **MOSI** pin
    - Arduino Uno **Pin 12** (MISO) to ATtiny85 **MISO** pin
    - Arduino Uno **Pin 13** (SCK) to ATtiny85 **SCK** pin

3. **Compile Your Code**: Compile your code into a `.hex` file using `avr-gcc` and `avr-objcopy`. For example:

    ```bash
    avr-gcc -mmcu=attiny85 -Os -o main.elf main.c
    avr-objcopy -O ihex -R .eeprom main.elf main.hex
    ```

4. **Upload `.hex` File**: Use AVRDUDE or a similar programming tool to upload the `.hex` file to the ATtiny85. For example:

    ```bash
    avrdude -c avrisp -p attiny85 -P <port> -b 19200 -U flash:w:main.hex
    ```    
    Replace `<port>` with the serial port connected to your Arduino Uno.

    for example my port was /dev/ttyACM0
    
    ```bash

    avrdude -c avrisp -p attiny85 -P /dev/ttyACM0 -b 19200 -U flash:w:main.hex
    ```

5. **Verify Upload**: After uploading the `.hex` file, verify that the programming was successful. AVRDUDE may provide feedback or confirmation messages.

6. **Reset ATtiny85**: Once the upload is complete, reset the ATtiny85 by power-cycling it or using the RESET pin.

7. **Run Program**: After resetting the ATtiny85, it should execute your program.
