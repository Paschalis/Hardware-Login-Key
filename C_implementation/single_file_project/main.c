#include <avr/io.h>               // AVR IO definitions
#include <avr/interrupt.h>        // AVR interrupt definitions
#define F_CPU 1000000UL           // AVR clock frequency, assuming 1MHz
#include <util/delay.h>           // AVR delay functions
#include <avr/pgmspace.h>         // AVR program memory space functions
#include <avr/eeprom.h>           // AVR EEPROM functions
#include <usbdrv/usbdrv.h>        // USB driver library
#include <aes/aes.h>              // AES library for encryption

// USB HID key codes for relevant keys
#define KEY_ENTER 0x28            // USB HID key code for Enter
#define KEY_S 0x16                // USB HID key code for 'S'
#define KEY_T 0x17                // USB HID key code for 'T'
#define KEY_U 0x18                // USB HID key code for 'U'
#define KEY_D 0x07                // USB HID key code for 'D'
#define KEY_Y 0x1C                // USB HID key code for 'Y'

// Global variable for the encryption key stored in EEPROM
const uint8_t encryptionKey[16] EEMEM = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};

// Function to encrypt the password using AES
void encryptPassword(uint8_t *password, uint8_t *encryptedPassword) {
    uint8_t key[16];
    // Read the encryption key from EEPROM
    eeprom_read_block((void *)key, (const void *)encryptionKey, 16);
    // Encrypt the password using AES ECB mode
    AES128_ECB_encrypt(password, key, encryptedPassword);
}

// USB setup function
usbMsgLen_t usbFunctionSetup(uint8_t data[8]) {
    return 0;
}

// USB write out function
void usbFunctionWriteOut(uint8_t *data, uint8_t len) {
    // No action needed
}

// Function to send USB HID keystroke
void USB_HID_Send(uint8_t key) {
    usbHidSend(&key, 1);          // Send USB HID key code
    _delay_ms(10);                // Delay to ensure key press is registered
}

int main(void) {
    // Plaintext password
    uint8_t password[16] = {KEY_S, KEY_T, KEY_U, KEY_D, KEY_Y};
    uint8_t encryptedPassword[16];

    // Set button pin as input with pull-up resistor
    DDRB &= ~(1 << PB0);
    PORTB |= (1 << PB0);

    // Initialize USB
    usbInit();
    usbDeviceDisconnect();
    _delay_ms(100);
    usbDeviceConnect();
    sei();                         // Enable global interrupts

    // Wait for button press
    while (1) {
        usbPoll();                 // Poll USB
        if (!(PINB & (1 << PB0))) {
            // Button pressed, send keystrokes for login
            USB_HID_Send(KEY_ENTER);    // Enter to wake up system
            _delay_ms(2000);             // Wait for system to wake up
            USB_HID_Send(KEY_S);         // Press 'S' to select username field
            USB_HID_Send(KEY_T);         // Enter username "study"
            USB_HID_Send(KEY_U);
            USB_HID_Send(KEY_D);
            USB_HID_Send(KEY_Y);
            USB_HID_Send(KEY_ENTER);     // Press Enter after entering username
            _delay_ms(1000);              // Wait for password field to appear
            encryptPassword(password, encryptedPassword);  // Encrypt the password
            for (int i = 0; i < 16; i++) {
                USB_HID_Send(encryptedPassword[i]);  // Send encrypted password
            }
            USB_HID_Send(KEY_ENTER);     // Press Enter to log in
            break;                       // Exit the loop after logging in
        }
    }

    // Main loop
    while (1) {
        usbPoll();                     // Poll USB
        // Your code here
    }

    return 0;
}
