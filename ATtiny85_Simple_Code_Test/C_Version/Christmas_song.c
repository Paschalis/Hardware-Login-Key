#include <avr/io.h>
#include "notes.h"

// --- Microcontroller Clock Speed ---
#ifndef F_CPU
#define F_CPU 8000000UL // 8MHz clock speed for ATtiny85
#endif

// --- Pin Definition ---
#define SPEAKER_PIN PB1 // Using PB1 (physical pin 6 on ATtiny85)

// --- Note and Melody Structure ---
typedef struct {
    uint16_t frequency;
    uint16_t duration;
} Note;

// --- Tempo and Note Durations (in milliseconds) ---
#define TEMPO 140
#define WHOLE_NOTE     (uint16_t)((60000.0 / TEMPO) * 4)
#define HALF_NOTE      (uint16_t)((60000.0 / TEMPO) * 2)
#define QUARTER_NOTE   (uint16_t)(60000.0 / TEMPO)
#define EIGHTH_NOTE    (uint16_t)((60000.0 / TEMPO) / 2)
#define SIXTEENTH_NOTE (uint16_t)((60000.0 / TEMPO) / 4)

// --- Song 1: "Jingle Bells" ---
Note jingle_bells_melody[] = {
    // Verse
    {NOTE_E5, QUARTER_NOTE}, {NOTE_E5, QUARTER_NOTE}, {NOTE_E5, HALF_NOTE},
    {NOTE_E5, QUARTER_NOTE}, {NOTE_E5, QUARTER_NOTE}, {NOTE_E5, HALF_NOTE},
    {NOTE_E5, QUARTER_NOTE}, {NOTE_G5, QUARTER_NOTE}, {NOTE_C5, QUARTER_NOTE + EIGHTH_NOTE}, {NOTE_D5, EIGHTH_NOTE}, {NOTE_E5, HALF_NOTE},
    {NOTE_F5, QUARTER_NOTE}, {NOTE_F5, QUARTER_NOTE}, {NOTE_F5, QUARTER_NOTE + EIGHTH_NOTE}, {NOTE_F5, EIGHTH_NOTE},
    {NOTE_F5, QUARTER_NOTE}, {NOTE_E5, QUARTER_NOTE}, {NOTE_E5, EIGHTH_NOTE}, {NOTE_E5, EIGHTH_NOTE},
    {NOTE_E5, QUARTER_NOTE}, {NOTE_D5, QUARTER_NOTE}, {NOTE_D5, QUARTER_NOTE}, {NOTE_E5, QUARTER_NOTE},
    {NOTE_D5, HALF_NOTE}, {NOTE_G5, HALF_NOTE}, {NOTE_REST, QUARTER_NOTE},
    // Chorus
    {NOTE_E5, QUARTER_NOTE}, {NOTE_E5, QUARTER_NOTE}, {NOTE_E5, HALF_NOTE},
    {NOTE_E5, QUARTER_NOTE}, {NOTE_E5, QUARTER_NOTE}, {NOTE_E5, HALF_NOTE},
    {NOTE_E5, QUARTER_NOTE}, {NOTE_G5, QUARTER_NOTE}, {NOTE_C5, QUARTER_NOTE + EIGHTH_NOTE}, {NOTE_D5, EIGHTH_NOTE}, {NOTE_E5, HALF_NOTE},
    {NOTE_F5, QUARTER_NOTE}, {NOTE_F5, QUARTER_NOTE}, {NOTE_F5, QUARTER_NOTE + EIGHTH_NOTE}, {NOTE_F5, EIGHTH_NOTE},
    {NOTE_F5, QUARTER_NOTE}, {NOTE_E5, QUARTER_NOTE}, {NOTE_E5, QUARTER_NOTE},
    {NOTE_G5, QUARTER_NOTE}, {NOTE_G5, QUARTER_NOTE}, {NOTE_F5, QUARTER_NOTE}, {NOTE_D5, QUARTER_NOTE}, {NOTE_C5, HALF_NOTE}, {NOTE_REST, QUARTER_NOTE}
};
int jingle_bells_length = sizeof(jingle_bells_melody) / sizeof(Note);

// --- Song 2: "We Wish You a Merry Christmas" ---
Note we_wish_you_melody[] = {
    {NOTE_G4, QUARTER_NOTE}, {NOTE_C5, QUARTER_NOTE}, {NOTE_C5, EIGHTH_NOTE}, {NOTE_D5, EIGHTH_NOTE}, {NOTE_C5, QUARTER_NOTE}, {NOTE_B4, QUARTER_NOTE}, {NOTE_A4, HALF_NOTE},
    {NOTE_A4, QUARTER_NOTE}, {NOTE_D5, QUARTER_NOTE}, {NOTE_D5, EIGHTH_NOTE}, {NOTE_E5, EIGHTH_NOTE}, {NOTE_D5, QUARTER_NOTE}, {NOTE_C5, QUARTER_NOTE}, {NOTE_B4, HALF_NOTE},
    {NOTE_B4, QUARTER_NOTE}, {NOTE_E5, QUARTER_NOTE}, {NOTE_E5, EIGHTH_NOTE}, {NOTE_F5, EIGHTH_NOTE}, {NOTE_E5, QUARTER_NOTE}, {NOTE_D5, QUARTER_NOTE}, {NOTE_C5, HALF_NOTE},
    {NOTE_G4, QUARTER_NOTE}, {NOTE_G4, QUARTER_NOTE}, {NOTE_A4, QUARTER_NOTE}, {NOTE_D5, HALF_NOTE}, {NOTE_B4, QUARTER_NOTE}, {NOTE_C5, HALF_NOTE}, {NOTE_REST, HALF_NOTE}
};
int we_wish_you_length = sizeof(we_wish_you_melody) / sizeof(Note);

// --- NEW: Song 3: "Deck the Halls" ---
Note deck_the_halls_melody[] = {
    {NOTE_G5, QUARTER_NOTE}, {NOTE_F5, EIGHTH_NOTE}, {NOTE_E5, QUARTER_NOTE}, {NOTE_D5, EIGHTH_NOTE}, {NOTE_C5, QUARTER_NOTE}, {NOTE_D5, QUARTER_NOTE}, {NOTE_E5, QUARTER_NOTE}, {NOTE_C5, QUARTER_NOTE},
    {NOTE_D5, QUARTER_NOTE}, {NOTE_E5, EIGHTH_NOTE}, {NOTE_F5, QUARTER_NOTE}, {NOTE_E5, EIGHTH_NOTE}, {NOTE_D5, QUARTER_NOTE}, {NOTE_C5, QUARTER_NOTE}, {NOTE_B4, QUARTER_NOTE}, {NOTE_G4, QUARTER_NOTE},
    {NOTE_A4, QUARTER_NOTE}, {NOTE_B4, QUARTER_NOTE}, {NOTE_C5, HALF_NOTE}, {NOTE_G5, QUARTER_NOTE}, {NOTE_F5, EIGHTH_NOTE}, {NOTE_E5, QUARTER_NOTE}, {NOTE_D5, EIGHTH_NOTE},
    {NOTE_C5, HALF_NOTE}, {NOTE_G5, QUARTER_NOTE}, {NOTE_F5, EIGHTH_NOTE}, {NOTE_E5, QUARTER_NOTE}, {NOTE_D5, EIGHTH_NOTE}, {NOTE_C5, HALF_NOTE}, {NOTE_REST, HALF_NOTE}
};
int deck_the_halls_length = sizeof(deck_the_halls_melody) / sizeof(Note);


// --- Helper Functions (no changes here) ---
void variable_delay_us(uint16_t us) {
    for (uint16_t i = 0; i < us; ++i) {
        __asm__ __volatile__ ("nop");
        __asm__ __volatile__ ("nop");
        __asm__ __volatile__ ("nop");
    }
}

void variable_delay_ms(uint16_t ms) {
    for (uint16_t i = 0; i < ms; ++i) {
        variable_delay_us(1000);
    }
}

void play_tone(uint16_t frequency, uint16_t duration_ms) {
    if (frequency == 0) {
        variable_delay_ms(duration_ms);
        return;
    }
    uint32_t period_us = 1000000UL / frequency;
    uint32_t half_period_us = period_us / 2;
    uint32_t total_cycles = (uint32_t)duration_ms * 1000 / period_us;

    for (uint32_t i = 0; i < total_cycles; ++i) {
        PORTB |= (1 << SPEAKER_PIN);
        variable_delay_us(half_period_us);
        PORTB &= ~(1 << SPEAKER_PIN);
        variable_delay_us(half_period_us);
    }
}


int main(void) {
    DDRB |= (1 << SPEAKER_PIN);

    while (1) {
        // --- Play Song 1: Jingle Bells ---
        for (int i = 0; i < jingle_bells_length; i++) {
            Note current_note = jingle_bells_melody[i];
            play_tone(current_note.frequency, current_note.duration);
            variable_delay_ms(50); // Short pause between notes
        }
        
        // --- Pause between songs ---
        variable_delay_ms(2000); 

        // --- Play Song 2: We Wish You a Merry Christmas ---
        for (int i = 0; i < we_wish_you_length; i++) {
            Note current_note = we_wish_you_melody[i];
            play_tone(current_note.frequency, current_note.duration);
            variable_delay_ms(50); // Short pause between notes
        }

        // --- Pause between songs ---
        variable_delay_ms(2000);

        // --- NEW: Play Song 3: Deck the Halls ---
        for (int i = 0; i < deck_the_halls_length; i++) {
            Note current_note = deck_the_halls_melody[i];
            play_tone(current_note.frequency, current_note.duration);
            variable_delay_ms(50); // Short pause between notes
        }

        // --- Pause before repeating the whole playlist ---
        variable_delay_ms(3000); 
    }
    return 0;
}