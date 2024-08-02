#include <avr/io.h>
#include <util/delay.h>
#include "DigisparkKeyboard/DigiKeyboard.h"

const int buttonPin = PB1; // Pin for the button
const char* password = "YourSecurePassword123"; // Password to be typed out

void setup() {
  DDRB &= ~(1 << buttonPin); // Set button pin as input
  PORTB |= (1 << buttonPin); // Enable pull-up resistor on button pin
}

void loop() {
  if (!(PINB & (1 << buttonPin))) {
    // Button is pressed
    DigiKeyboard.sendKeyStroke(0); // Required to send an empty report to wake up the host
    DigiKeyboard.print(password); // Type out the password
    _delay_ms(1000); // Debounce delay
  }
}

int main(void) {
  setup();
  while (1) {
    loop();
  }
}
