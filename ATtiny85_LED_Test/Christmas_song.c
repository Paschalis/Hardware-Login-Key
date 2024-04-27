#include <avr/io.h>
#define F_CPU 1000000UL  // Assuming a clock frequency of 1MHz
#include <util/delay.h>

int main(void) {
    // Set PB1 (physical pin 6) as output
    DDRB |= (1 << PB1);

    while (1) {
        // Blink pattern for "Jingle Bells"
        for (int i = 0; i < 3; i++) {
            PORTB |= (1 << PB1); // Turn on LED
            _delay_ms(2000);      // Delay
            PORTB &= ~(1 << PB1); // Turn off LED
            _delay_ms(2000);       // Delay
        }
        _delay_ms(4000); // Additional delay between repetitions
    }

    return 0;
}
