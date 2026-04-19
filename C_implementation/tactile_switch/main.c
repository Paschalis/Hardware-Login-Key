#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usbdrv/usbdrv.h"

// --- Pin Definitions ---
#define BUTTON_PIN  PB1 // Button is on PB1

// --- HID Keyboard Report Descriptor ---
PROGMEM const char usbHidReportDescriptor[63] = {
    0x05, 0x01, 0x09, 0x06, 0xa1, 0x01, 0x75, 0x01, 0x95, 0x08, 0x05, 0x07, 0x19, 0xe0, 0x29, 0xe7,
    0x15, 0x00, 0x25, 0x01, 0x81, 0x02, 0x95, 0x01, 0x75, 0x08, 0x81, 0x03, 0x95, 0x05, 0x75, 0x01,
    0x05, 0x08, 0x19, 0x01, 0x29, 0x05, 0x91, 0x02, 0x95, 0x01, 0x75, 0x03, 0x91, 0x03, 0x95, 0x06,
    0x75, 0x08, 0x15, 0x00, 0x25, 0x65, 0x05, 0x07, 0x19, 0x00, 0x29, 0x65, 0x81, 0x00, 0xc0
};

// This is the COMPLEX SUFFIX of your password.
static const char password_suffix[] = "!#2025_complex";

// Function to send a keystroke
void send_key(uchar key_code, uchar modifier) {
    static uchar reportBuffer[8] = {0};
    reportBuffer[0] = modifier;
    reportBuffer[2] = key_code;

    while (!usbInterruptIsReady()) {
        usbPoll();
        _delay_ms(5);
    }
    usbSetInterrupt(reportBuffer, sizeof(reportBuffer));

    reportBuffer[0] = 0;
    reportBuffer[2] = 0;
    while (!usbInterruptIsReady()) {
        usbPoll();
        _delay_ms(5);
    }
    usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
}

// Function to type out the password string
void type_password() {
    for (int i = 0; i < sizeof(password_suffix) - 1; i++) {
        char c = password_suffix[i];
        uchar key_code = 0;
        uchar modifier = 0;

        if (c >= 'a' && c <= 'z') { key_code = c - 'a' + 4; }
        else if (c >= 'A' && c <= 'Z') { key_code = c - 'A' + 4; modifier = 0x02; }
        else if (c >= '1' && c <= '9') { key_code = c - '1' + 30; }
        else if (c == '0') { key_code = 39; }
        else if (c == '!') { key_code = 30; modifier = 0x02; }
        else if (c == '#') { key_code = 32; modifier = 0x02; }
        else if (c == '_') { key_code = 45; modifier = 0x02; }
        else if (c == '-') { key_code = 45; }

        if (key_code != 0) {
            send_key(key_code, modifier);
            _delay_ms(50);
        }
    }
    send_key(40, 0); // Press Enter
}

int main(void) {
    // --- Setup ---
    wdt_disable();

    // Setup Button Pin
    DDRB &= ~(1 << BUTTON_PIN); // Set BUTTON_PIN (PB1) as input
    PORTB |= (1 << BUTTON_PIN); // Enable internal pull-up for BUTTON_PIN

    // Initialize V-USB
    usbInit();
    usbDeviceDisconnect();
    for (int i = 0; i < 250; i++) { _delay_ms(1); }
    usbDeviceConnect();

    sei(); // Enable global interrupts

    // --- Main Loop ---
    while (1) {
        usbPoll();
        if (!(PINB & (1 << BUTTON_PIN))) { // Check if button is pressed
            _delay_ms(20); // Debounce
            if (!(PINB & (1 << BUTTON_PIN))) {
                type_password();
                // Wait for button to be released
                while (!(PINB & (1 << BUTTON_PIN))) {
                    usbPoll();
                }
            }
        }
    }
    return 0;
}

// --- V-USB Required Callback Functions ---

// This function is called by V-USB for every incoming control message.
// We are only a keyboard, so we don't need to handle any custom requests.
// We just return 0 to indicate that we haven't handled the request.
USB_PUBLIC uchar usbFunctionSetup(uchar data[8]) {
    usbRequest_t    *rq = (void *)data;

    // The host requests the HID report descriptor.
    if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_STANDARD){
        if(rq->bRequest == USBRQ_GET_DESCRIPTOR){
            if(rq->wValue.bytes[1] == USBDESCR_HID_REPORT){
                usbMsgPtr = (void *)usbHidReportDescriptor;
                return sizeof(usbHidReportDescriptor);
            }
        }
    }
    // All other requests are not handled.
    return 0;
}