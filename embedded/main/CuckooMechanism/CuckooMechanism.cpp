/**
 *
 */

#include "CuckooMechanism.h"
#include "RtcDateTime.h"

#include <utility>

CuckooMechanism::CuckooMechanism() = default;

/**
 * Initialize the cuckoo mechanism by attaching the servo motor and moving it to the starting position.
 */
void CuckooMechanism::initialize(Screen givenScreen) {
    motor.attach(SERVO_PIN);
    motor.write(0);
    screen = std::move(givenScreen);
    screen.createCustomCharacter(PAC_MAN_CHARACTER, pacMan);
    screen.createCustomCharacter(GHOST_CHARACTER, ghost);
    screen.createCustomCharacter(DOT_CHARACTER, dot);
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
 * Display the cuckoo state on the screen.
 * The first line shows the time.
 * The second line shows Pac-Man related characters
 * @param dateTime
 */
void CuckooMechanism::displayCuckooState(RtcDateTime dateTime) {
    String timeString = "It's ";

    // If it is a full hour, print the hour
    if (dateTime.Minute() == 0 && dateTime.Second() == 0) {
        timeString += String(dateTime.Hour()) + " o'clock";
    } else {
        const int TIME_STRING_SIZE = 6;
        char currentTimeString[TIME_STRING_SIZE];
        sprintf(currentTimeString, "%02d:%02d", dateTime.Minute(), dateTime.Second());
        timeString += currentTimeString;
    }

    // Center timeString
    int timeStringPadding = static_cast<int>(CHARACTERS_PER_LINE - timeString.length()) / 2;
    for (int i = 0; i < timeStringPadding; i++) {
        timeString = " " + timeString;
    }

    screen.clear();
    screen.printText(timeString, 0, 0);

    // Print the following: " X ･･････････ Y " where X represents Pac-Man and Y the ghost
    const int SECOND_LINE = 1;
    for (int position = 0; position < CHARACTERS_PER_LINE; position++) {
        // Check if the position should be skipped
        if (position == 0 || position == 2 || position == 13 || position == 15) {
            continue;
        }

        // Print pac-man at position 1, then move on to the next position
        if (position == 1) {
            screen.printCustomCharacter(position, SECOND_LINE, byte(PAC_MAN_CHARACTER));
            continue;
        }

        // Print ghost at position 14, then move on to the next position
        if (position == 14) {
            screen.printCustomCharacter(position, SECOND_LINE, byte(GHOST_CHARACTER));
            continue;
        }

        // Else, print a dot
        screen.printCustomCharacter(position, SECOND_LINE, byte(DOT_CHARACTER));
    }
}

/**
 * Execute the cuckoo mechanism by moving the cuckoo forward, playing the melody and moving the cuckoo backward.
 */
void CuckooMechanism::executeCuckooMechanism(RtcDateTime time) {
    Serial.println("Executing cuckoo mechanism.");
    displayCuckooState(time);
    moveCuckooForward();
    playMelody();
    moveCuckooBackward();
}