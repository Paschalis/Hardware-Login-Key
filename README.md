# 🔐 Hardware Login Key

![Under Construction](https://img.shields.io/badge/status-under%20construction-orange)


## Introduction
This project provides a simple solution for securely logging into a system or website using a hardware key. By pressing a physical button connected to an ATtiny85 microcontroller, users can automate the login process, reducing the risk of password exposure.

## 🎯 Purpose
The purpose of this project is to offer a more secure alternative to typing long or complex passwords manually, especially in environments where there may be observers or surveillance. With the hardware key, users can log in quickly and securely without the risk of their password being intercepted or observed.

## Benefits
- **Enhanced Security:** Eliminates the risk of password interception by keystroke loggers or shoulder surfing.
- **Convenience:** Simplifies the login process, particularly for systems with lengthy or complex passwords.
- **Privacy:** Protects the confidentiality of passwords in public or shared environments.
- **Portability:** Can be easily carried and used on multiple systems or devices.

## How it Works
The hardware key is based on an ATtiny85 microcontroller using V-USB library to implement USB Human Interface Device (HID) keyboard functionality. This allows the ATtiny85 to act as a keyboard when connected to a computer via USB. When the button connected to the ATtiny85 is pressed, it sends predefined keystrokes to the computer, automating the login process.

## 📁 Folder Structure (C and C++)
- 📁 **Hardware-Login-Key**
  - 📁 **C_implementation**
    - 📁 **single_file_project**
      - 📄 main.c
      - 📄 Makefile
    - 📁 **multi_file_project**
      - 📄 main.c
      - 📄 aes.c
      - 📄 Makefile
  - 📁 **CPP_implementation**
    - 📁 **single_file_project**
      - 📄 main.cpp
      - 📄 Makefile
    - 📁 **multi_file_project**
      - 📄 main.cpp
      - 📄 aes.c
      - 📄 Makefile
  - 📁 **3d_printed_case**
    - 📄 hardware_key_case.stl

## Compilation Instructions

### C Implementation
To compile the C implementation, follow these steps:

1. Open a terminal.
2. Navigate to the `C_implementation` folder.
3. Read the [instructions](INSTRUCTIONS_C.md) for C implementation.

### C++ Implementation
To compile the C++ implementation, follow these steps:

1. Open a terminal.
2. Navigate to the `CPP_implementation` folder.
3. Read the [instructions](INSTRUCTIONS_CPP.md) for C++ implementation.

## 📋 Usage
1. Connect the hardware key to the computer.
2. Press the button on the hardware key.
3. The hardware key sends the predefined keystrokes for logging in.
4. The user is logged in securely without typing the password manually.

## 🛒 Requirements
- ATtiny85 microcontroller
- Button or switch
- USB cable
- Computer with USB port
- Development environment (e.g., AVR-GCC, avrdude) for programming the ATtiny85

## Security Considerations
- Ensure the physical security of the hardware key to prevent unauthorized access.
- Keep the key firmware up-to-date to mitigate potential security vulnerabilities.
- Do not use the hardware key on untrusted or compromised systems.
- Use strong encryption and authentication methods in addition to the hardware key for robust security.

## 🏗️ 3D Printed Case
A 3D printed case is available for the hardware key. To use it, follow these steps:

1. Open the `3d_printed_case` folder.
2. Load the `hardware_key_case.stl` file into your 3D printer software.
3. Print the case using your 3D printer.
4. Once printed, assemble the hardware key inside the case for added protection and aesthetics.

## 📜 License

This project is licensed under the [MIT License](LICENSE).

- [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)


**Enjoy** your secure **hardware** login key 🔐! **Thank you for visiting Hardware-Login-Key!** ✨

