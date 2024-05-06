### Running AVR Project with Makefile

Follow these steps to compile and upload your AVR project using the provided Makefile.

#### Prerequisites

1. **AVR Toolchain**: Ensure you have AVR-GCC and AVRDUDE installed on your system.
2. **Connect Arduino Uno as ISP**: Connect your Arduino Uno to your computer via USB. Then, connect the following pins from the Arduino Uno to the ATtiny85:
    - Arduino Uno **5V** pin to ATtiny85 **VCC** pin
    - Arduino Uno **GND** pin to ATtiny85 **GND** pin
    - Arduino Uno **Pin 10** (SS) to ATtiny85 **RESET** pin
    - Arduino Uno **Pin 11** (MOSI) to ATtiny85 **MOSI** pin
    - Arduino Uno **Pin 12** (MISO) to ATtiny85 **MISO** pin
    - Arduino Uno **Pin 13** (SCK) to ATtiny85 **SCK** pin
3. **Terminal**: Open a terminal window in the directory containing your AVR project files.

#### Instructions

1. **Download Makefile**: Save the provided Makefile in the root directory of your AVR project.

2. **Edit Makefile (Optional)**: If necessary, modify the Makefile variables to match your setup:
   - `MCU`: Specify the AVR microcontroller model (e.g., `attiny85`).
   - `F_CPU`: Define the CPU frequency in Hz (e.g., `8000000UL` for 8MHz).
   - `BAUDRATE`: Set the baud rate for communication with the Arduino Uno (default is `19200`).
   - `PORT`: Define the serial port connected to your Arduino Uno (e.g., `/dev/ttyACM0`).

3. **Compile Code**: Run the following command in the terminal to compile your code and generate the `.hex` file:

```bash
make
```

4. **Upload Firmware**: Use the following command to upload the generated `.hex` file to your ATtiny85:


```bash
make flash
```


Ensure that your Arduino Uno is connected and replace `/dev/ttyACM0` with the appropriate serial port if necessary.

5. **Verify Upload**: After successful upload, verify that your AVR device is functioning as expected.

6. **Clean**: If needed, clean up generated files by running:

```bash
make clean
```

This will remove object files (`*.o`), the `.hex` file, and the executable (`*.elf`).

#### Additional Notes

- Ensure AVRDUDE is properly configured with the correct programmer (`-c` option) and fuse settings if required.
- Consult the datasheet of your AVR microcontroller for specific fuse settings and programming considerations.
- Troubleshoot any compilation or upload errors by checking terminal output and verifying connections.
