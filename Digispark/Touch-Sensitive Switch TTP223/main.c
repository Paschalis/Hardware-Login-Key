#include <avr/io.h>
#include <util/delay.h>
#include "DigisparkKeyboard/DigiKeyboard.h"

#define TOUCH_PIN PB1 // Example pin for TTP223 output

void init_ports() {
    DDRB &= ~(1 << TOUCH_PIN); // Set TOUCH_PIN as input
    PORTB |= (1 << TOUCH_PIN); // Enable pull-up resistor on TOUCH_PIN
}

int main(void) {
    init_ports();
    while (1) {
        if (PINB & (1 << TOUCH_PIN)) {
            // Touch not detected
        } else {
            // Touch detected
            DigiKeyboard.sendKeyStroke(0); // Required to send an empty report to wake up the host
            DigiKeyboard.print(password); // Type out the password
            _delay_ms(1000); // Debounce delay
        }
        _delay_ms(100); // Delay to avoid bouncing
    }
}
