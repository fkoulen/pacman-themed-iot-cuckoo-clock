/**
 *
 */

#include "CuckooMechanism.h"

CuckooMechanism::CuckooMechanism() = default;

/**
 * Play the Pac-Man melody.
 */
void CuckooMechanism::playMelody() {
    Serial.println("Playing melody.");
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