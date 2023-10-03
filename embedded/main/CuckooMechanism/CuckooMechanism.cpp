/**
 *
 */

#include "CuckooMechanism.h"

CuckooMechanism::CuckooMechanism() = default;

/**
 * Initialize the cuckoo mechanism by attaching the servo motor and moving it to the starting position.
 */
void CuckooMechanism::initialize() {
    motor.attach(SERVO_PIN);
    motor.write(0);
}

/**
 * Play the Pac-Man melody.
 */
void CuckooMechanism::playMelody() {
    Serial.println("Playing melody.");
    double thisNoteDuration, noteDurationInMs = 0;

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
        tone(BUZZER_PIN, melody[thisNote], static_cast<int>(noteDurationInMs * 0.9));

        // Wait for the specified duration before playing the next note.
        delay(static_cast<int>(noteDurationInMs));

        // Stop playing the note.
        noTone(BUZZER_PIN);
    }
}

/**
 * Move the cuckoo forward.
 */
void CuckooMechanism::moveCuckooForward() {
    Serial.println("Moving cuckoo forward.");
    motor.write(180);
}

/**
 * Move the cuckoo backward.
 */
void CuckooMechanism::moveCuckooBackward() {
    Serial.println("Moving cuckoo backward.");
    motor.write(0);
}

/**
 * Move the cuckoo forward, play the melody and move the cuckoo backward.
 */
void CuckooMechanism::moveCuckooAndPlayMelody() {
    moveCuckooForward();
    playMelody();
    moveCuckooBackward();
}