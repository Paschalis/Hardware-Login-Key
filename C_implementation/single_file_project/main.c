// avr-gcc -mmcu=attiny85 -Os -DF_CPU=16000000UL -o main.elf main.c usbdrv.c

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include "usbdrv.h"

#define BUTTON_PIN   PB1  // Pin connected to the button
#define BUTTON_DDR   DDRB
#define BUTTON_PORT  PORTB

// Define the HID report descriptor length
#define USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH 29

// USB Configuration
USB_PUBLIC uchar usbFunctionSetup(uchar data[8]) {
    return 0; // No additional setup needed
}

// USB Report Descriptor - Keyboard
PROGMEM const char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x75, 0x01,                    // REPORT_SIZE (1)
    0x95, 0x08,                    // REPORT_COUNT (8)
    0x05, 0x07,                    // USAGE_PAGE (Keyboard)
    0x19, 0xe0,                    // USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                    // USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    // LOGICAL_MINIMUM (0)
    0x25, 0x01,                    // LOGICAL_MAXIMUM (1)
    0x81, 0x02,                    // INPUT (Data,Var,Abs) ; Modifier byte
    0x95, 0x01,                    // REPORT_COUNT (1)
    0x75, 0x08,                    // REPORT_SIZE (8)
    0x81, 0x03,                    // INPUT (Cnst,Var,Abs) ; Reserved byte
    0x95, 0x05,                    // REPORT_COUNT (5)
    0x75, 0x01,                    // REPORT_SIZE (1)
    0x05, 0x08,                    // USAGE_PAGE (LEDs)
    0x19, 0x01,                    // USAGE_MINIMUM (Num Lock)
    0x29, 0x05,                    // USAGE_MAXIMUM (Kana)
    0x91, 0x02,                    // OUTPUT (Data,Var,Abs) ; LED report
    0x95, 0x01,                    // REPORT_COUNT (1)
    0x75, 0x03,                    // REPORT_SIZE (3)
    0x91, 0x03,                    // OUTPUT (Cnst,Var,Abs) ; LED report padding
    0x95, 0x06,                    // REPORT_COUNT (6)
    0x75, 0x08,                    // REPORT_SIZE (8)
    0x15, 0x00,                    // LOGICAL_MINIMUM (0)
    0x25, 0x65,                    // LOGICAL_MAXIMUM (101)
    0x05, 0x07,                    // USAGE_PAGE (Keyboard)
    0x19, 0x00,                    // USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x65,                    // USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,                    // INPUT (Data,Ary,Abs)
    0xc0                           // END_COLLECTION
};

// USB Initialization
void usbInit(void) {
    usbDeviceDisconnect();   // Disconnect USB
    _delay_ms(100);
    usbDeviceConnect();      // Connect USB
    usbInitEndpoints();      // Initialize Endpoints
    sei();                   // Enable Interrupts
}

// USB Keyboard Functions
void usbKeyboardSend(uchar key) {
    uchar keycode[2] = {0, key};
    usbSetInterrupt(usbHidReportDescriptor, keycode, sizeof(keycode));
    usbPoll();
}

// Main Function
int main(int argc, char *argv[]) {
    if (argc < 2) {
        // Print usage message if no password argument is provided
        printf("Usage: %s <password>\n", argv[0]);
        return 1; // Error: No password argument provided
    } else if (argc > 2) {
        // Print message if more than one argument is provided
        printf("Error: Too many arguments.\n");
        printf("Usage: %s <password>\n", argv[0]);
        return 1;
    }

    // Initialize USB
    usbInit();

    // Initialize Button Pin
    BUTTON_DDR &= ~(1 << BUTTON_PIN);  // Set as input
    BUTTON_PORT |= (1 << BUTTON_PIN);  // Enable pull-up resistor

    // Wait for button press
    while (BUTTON_PIN & (1 << BUTTON_PIN));  // Wait for button press

    // Loop through each character in the password argument
    char *password = argv[1];
    while (*password != '\0') {
        usbKeyboardSend(*password++);
        _delay_ms(10); // Delay between keystrokes
    }

    return 0;
}
