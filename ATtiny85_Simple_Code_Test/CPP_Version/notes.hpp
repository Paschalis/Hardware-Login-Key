#ifndef NOTES_HPP
#define NOTES_HPP

#include <stdint.h>

// --- Note Frequency Definitions (in Hz) ---
// A rest is defined as 0 Hz.
#define NOTE_REST 0

// Octave 4
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494

// Octave 5
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5  988

// --- Note and Melody Structure ---
// This struct will be used by the Song class.
struct Note {
    uint16_t frequency;
    uint16_t duration;
};

#endif // NOTES_HPP
