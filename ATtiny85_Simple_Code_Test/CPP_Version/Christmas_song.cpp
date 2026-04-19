#include <avr/io.h>
#include "notes.hpp"

// --- Microcontroller Clock Speed ---
#ifndef F_CPU
#define F_CPU 8000000UL // 8MHz clock speed for ATtiny85
#endif

// --- Helper function for variable microsecond delays ---
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

// --- Class Definitions ---

/**
 * @class Song
 * @brief Encapsulates a melody, which is an array of notes and its length.
 */
class Song {
public:
    const Note* const melody;
    const int length;

    Song(const Note* songMelody, int songLength)
        : melody(songMelody), length(songLength) {}
};

/**
 * @class Speaker
 * @brief Manages a speaker pin to play tones and songs.
 */
class Speaker {
private:
    uint8_t _pin;

public:
    Speaker(uint8_t pin) : _pin(pin) {
        // Set the speaker pin as an output
        DDRB |= (1 << _pin);
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
            PORTB |= (1 << _pin);
            variable_delay_us(half_period_us);
            PORTB &= ~(1 << _pin);
            variable_delay_us(half_period_us);
        }
    }

    void play(const Song& song) {
        for (int i = 0; i < song.length; ++i) {
            Note current_note = song.melody[i];
            play_tone(current_note.frequency, current_note.duration);
            variable_delay_ms(50); // Pause between notes
        }
    }
};

// --- Tempo and Note Durations ---
#define TEMPO 140
#define WHOLE_NOTE     (uint16_t)((60000.0 / TEMPO) * 4)
#define HALF_NOTE      (uint16_t)((60000.0 / TEMPO) * 2)
#define QUARTER_NOTE   (uint16_t)(60000.0 / TEMPO)
#define EIGHTH_NOTE    (uint16_t)((60000.0 / TEMPO) / 2)

// --- Melody Data ---
const Note jingle_bells_melody[] = {
    {NOTE_E5, QUARTER_NOTE}, {NOTE_E5, QUARTER_NOTE}, {NOTE_E5, HALF_NOTE},
    {NOTE_E5, QUARTER_NOTE}, {NOTE_E5, QUARTER_NOTE}, {NOTE_E5, HALF_NOTE},
    {NOTE_E5, QUARTER_NOTE}, {NOTE_G5, QUARTER_NOTE}, {NOTE_C5, QUARTER_NOTE + EIGHTH_NOTE}, {NOTE_D5, EIGHTH_NOTE}, {NOTE_E5, HALF_NOTE}
    // ... (rest of the song can be added here)
};

const Note we_wish_you_melody[] = {
    {NOTE_G4, QUARTER_NOTE}, {NOTE_C5, QUARTER_NOTE}, {NOTE_C5, EIGHTH_NOTE}, {NOTE_D5, EIGHTH_NOTE}, {NOTE_C5, QUARTER_NOTE}, {NOTE_B4, QUARTER_NOTE}, {NOTE_A4, HALF_NOTE}
    // ...
};

const Note deck_the_halls_melody[] = {
    {NOTE_G5, QUARTER_NOTE}, {NOTE_F5, EIGHTH_NOTE}, {NOTE_E5, QUARTER_NOTE}, {NOTE_D5, EIGHTH_NOTE}, {NOTE_C5, QUARTER_NOTE}, {NOTE_D5, QUARTER_NOTE}, {NOTE_E5, QUARTER_NOTE}, {NOTE_C5, QUARTER_NOTE}
    // ...
};


int main(void) {
    // --- Setup ---
    Speaker speaker(PB1);

    // Create Song objects
    Song jingleBells(jingle_bells_melody, sizeof(jingle_bells_melody) / sizeof(Note));
    Song weWishYou(we_wish_you_melody, sizeof(we_wish_you_melody) / sizeof(Note));
    Song deckTheHalls(deck_the_halls_melody, sizeof(deck_the_halls_melody) / sizeof(Note));

    Song playlist[] = {jingleBells, weWishYou, deckTheHalls};

    // --- Main Loop ---
    while (1) {
        for (const auto& song : playlist) {
            speaker.play(song);
            variable_delay_ms(2000); // Pause between songs
        }
    }

    return 0; // Should never be reached
}
