/**
 * Play the Pac-Man sound.
 *
 * @author Robson Couto
 * @see https://github.com/robsoncouto/arduino-songs/blob/master/pacman/pacman.ino
 * @editor F.S. Koulen
 * @date 2023-09-30
 */

#include <Arduino.h>
#include "Pitches.h"

#define BPM 105;
#define BUZZER_PIN 14

/**
 * Notes of the melody followed by the duration.
 * A 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on.
 * Negative numbers are used to represent dotted notes,
 * so -4 means a dotted quarter note, that is, a quarter plus an eighteenth.
 */
const int melody[] = {

        // Pacman
        // Score available at https://musescore.com/user/85429/scores/107109
        NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, //1
        NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16,
        NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32, NOTE_G6, -16, NOTE_E6, 8,

        NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, NOTE_B5, 32,  //2
        NOTE_FS5, -16, NOTE_DS5, 8, NOTE_DS5, 32, NOTE_E5, 32, NOTE_F5, 32,
        NOTE_F5, 32, NOTE_FS5, 32, NOTE_G5, 32, NOTE_G5, 32, NOTE_GS5, 32, NOTE_A5, 16, NOTE_B5, 8
};

/**
 * The number of notes.
 * Since each note is represented by two values (pitch and duration),
 * the number of notes is half the size of the melody.
 */
const int notes = sizeof(melody) / sizeof(melody[0]) / 2;

/**
 * The duration of a whole note in ms.
 * Calculated by dividing 60000 (ms in a minute) multiplied by 4 (quarter notes) by the BPM.
 */
const int wholeNote = (60000 * 4) / BPM;


/**
 * Play the Pac-Man melody.
 */
void playMelody() {
    double thisNoteDuration, noteDurationInMs;

    /**
     * Iterate over the notes of the melody.
     * Remember, the array is twice the number of notes (notes + durations)
     */
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // Get the type of note (duration).
        thisNoteDuration = melody[thisNote + 1];

        // Check if there is a negative value, indicating a dotted note.
        if (thisNoteDuration > 0) {
            // If not, the duration is a regular note.
            noteDurationInMs = (wholeNote) / thisNoteDuration;
        } else if (thisNoteDuration < 0) { // If so, the duration is a dotted note.
            noteDurationInMs = (wholeNote) / abs(thisNoteDuration);
            noteDurationInMs *= 1.5; // A dotted note is 1.5 times longer than a regular note.
        }

        // Play the note on the buzzer. Only play 90% of the note, to avoid overlapping notes.
        tone(BUZZER_PIN, melody[thisNote], noteDurationInMs * 0.9);

        // Wait for the specified duration before playing the next note.
        delay(noteDurationInMs);

        // Stop playing the note.
        noTone(BUZZER_PIN);
    }
}

void setup() {
    playMelody();
}

void loop() {
    // no need to repeat the melody.
}