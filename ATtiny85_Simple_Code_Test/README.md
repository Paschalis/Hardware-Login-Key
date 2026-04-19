# Christmas Song Playlist for ATtiny85

This project contains the code to play a playlist of three Christmas songs on an ATtiny85 microcontroller. It is available in two separate versions: a standard C implementation and an object-oriented C++ implementation.

The playlist includes:
1.  Jingle Bells
2.  We Wish You a Merry Christmas
3.  Deck the Halls

## Project Structure

The repository is organized into two self-contained folders, each representing a complete version of the project:

*   **`C_Version/`**: A straightforward, procedural implementation using C (`.c`, `.h`).
*   **`CPP_Version/`**: An object-oriented implementation using C++ (`.cpp`, `.hpp`), which organizes the code into `Song` and `Speaker` classes.

Each folder contains its own source code and a dedicated `Makefile`.

## Option 1: Using the Makefile (Recommended)

This is the easiest and quickest way to compile and upload the code. The process is the same for both versions.

1.  **Navigate to the desired version's folder.**
    ```bash
    # To use the C++ version
    cd CPP_Version/
    
    # OR
    
    # To use the C version
    cd C_Version/
    ```

2.  **Compile the code.**
    This command builds the project and creates the `.hex` file.
    ```bash
    make
    ```

3.  **Upload to the ATtiny85.**
    This will compile if needed and then upload the program.
    ```bash
    make upload
    ```

4.  **(Optional) Clean up generated files.**
    ```bash
    make clean
    ```

## Option 2: Manual Compilation

If you prefer to run the commands yourself, follow these steps.

### For the C++ Version

1.  **Navigate to the C++ directory:**
    ```bash
    cd CPP_Version/
    ```
2.  **Compile with `avr-g++`:**
    ```bash
    avr-g++ -mmcu=attiny85 -DF_CPU=8000000UL -Os -o Christmas_song.elf Christmas_song.cpp
    ```
3.  **Create the HEX file:**
    ```bash
    avr-objcopy -O ihex -R .eeprom Christmas_song.elf Christmas_song.hex
    ```
4.  **Upload to the ATtiny85:**
    ```bash
    avrdude -c arduino -p attiny85 -P /dev/ttyACM0 -b 19200 -U flash:w:Christmas_song.hex
    ```

### For the C Version

1.  **Navigate to the C directory:**
    ```bash
    cd C_Version/
    ```
2.  **Compile with `avr-gcc`:**
    ```bash
    avr-gcc -mmcu=attiny85 -DF_CPU=8000000UL -Os -o Christmas_song.elf Christmas_song.c
    ```
3.  **Create the HEX file:**
    ```bash
    avr-objcopy -O ihex -R .eeprom Christmas_song.elf Christmas_song.hex
    ```
4.  **Upload to the ATtiny85:**
    ```bash
    avrdude -c arduino -p attiny85 -P /dev/ttyACM0 -b 19200 -U flash:w:Christmas_song.hex
    ```

## Demo

Listen to a recording of the ATtiny85 playing the song playlist:

**[▶️ Listen to the Song Demo](./assets/song_demo.mp3)**

## Requirements
- ATtiny85 microcontroller
- Speaker or Piezo Buzzer (or an LED for visual feedback)
- Arduino Uno (or another AVR programmer)
- Linux environment with `avr-gcc`, `avr-g++`, `avr-objcopy`, and `avrdude` installed

## Notes

> [!IMPORTANT]
> Ensure that the wiring between your programmer (e.g., Arduino Uno) and the ATtiny85 is correct before uploading. Incorrect wiring can prevent programming or damage the chip.
> 
> For more detailed wiring instructions, see the instruction files:
> - **[See the C Instructions](../INSTRUCTIONS_C.md)**
> - **[See the C++ Instructions](../INSTRUCTIONS_CPP.md)**

> [!NOTE]
> The speaker/buzzer should be connected to **PB1** (physical pin 6 on the ATtiny85) and Ground.

> [!TIP]
> If you don't have a speaker, you can connect an LED (with an appropriate current-limiting resistor) to the same pin (PB1). The LED will blink in the rhythm of the songs, which is a great way to debug and confirm that the code is running correctly.

> [!NOTE]
> You may need to adjust the `PORT` variable inside the `Makefile` in each directory to match the port your programmer is connected to on your system.

[⬅️ Go Back to Main README](../README.md)