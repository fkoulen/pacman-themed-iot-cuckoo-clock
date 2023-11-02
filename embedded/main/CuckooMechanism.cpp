/**
 * Implementation of the cuckoo mechanism.
 * Contains methods to play the melody, move the cuckoo and display the cuckoo state.
 *
 * @author F.S. Koulen
 * @details License: GNU GPLv3
 * <br/>
 */

#include "CuckooMechanism.h"


/**
 * Create an instance of the CuckooMechanism class.
 */
CuckooMechanism::CuckooMechanism() = default;

/**
 * Initialize the cuckoo mechanism by attaching the servo motor and moving it to the starting position.
 * It also sets the screen to use for displaying the cuckoo state and creates the custom characters.
 *
 * @param givenScreen The screen to use for displaying the cuckoo state
 */
void CuckooMechanism::initialize(Screen *givenScreen) {
    motor.attach(SERVO_PIN);
    motor.write(SERVO_START_POSITION);
    this->screen = givenScreen;
    screen->createCustomCharacter(PAC_MAN_CHARACTER, pacMan);
    screen->createCustomCharacter(GHOST_CHARACTER, ghost);
    screen->createCustomCharacter(DOT_CHARACTER, dot);
}

/**
 * Execute the cuckoo mechanism by displaying the cuckoo state, moving the cuckoo forward, playing the melody and
 * moving the cuckoo backward.
 *
 * @param time The current time to display on the screen and to check if the night mode is active. The melody is not
 *             played when the night mode is active.
 */
void CuckooMechanism::executeCuckooMechanism(RtcDateTime time) {
    Serial.println("Executing cuckoo mechanism.");
    displayCuckooState(time);

    moveCuckooForward();
    // If the time is not in the night mode, play the melody
    if (time.Hour() >= END_NIGHT_MODE && time.Hour() <= START_NIGHT_MODE) {
        playMelody();
    } else { // Else, wait for the duration of the melody
        Serial.println("Night mode is active, not playing melody.");
        delay(DURATION_OF_CUCKOO_IN_NIGHT);
    }

    moveCuckooBackward();
}

/**
 * Play the Pac-Man melody on the buzzer.
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

        // If the duration is positive, the duration is a regular note.
        if (thisNoteDuration > 0) {
            // If not, the duration is a regular note.
            noteDurationInMs = (wholeNote) / thisNoteDuration;
        } else if (thisNoteDuration < 0) { // If the duration is negative, the duration is a dotted note.
            noteDurationInMs = (wholeNote) / abs(thisNoteDuration);
            noteDurationInMs *= DOTTED_NOTE_MULTIPLIER; // A dotted note is 1.5 times longer than a regular note.
        }

        // Play the note on the buzzer. Only play 90% of the note, to avoid overlapping notes.
        tone(BUZZER_PIN, melody[thisNote], static_cast<int>(noteDurationInMs * NOTE_DURATION_MULTIPLIER));

        // Wait for the specified duration before playing the next note.
        delay(static_cast<int>(noteDurationInMs));

        // Stop playing the note.
        noTone(BUZZER_PIN);
    }
}

/**
 * Move the cuckoo forward by rotating the servo motor to the end position.
 */
void CuckooMechanism::moveCuckooForward() {
    Serial.println("Moving cuckoo forward.");
    motor.write(SERVO_END_POSITION);
}

/**
 * Move the cuckoo backward by rotating the servo motor back to the starting position.
 */
void CuckooMechanism::moveCuckooBackward() {
    Serial.println("Moving cuckoo backward.");
    motor.write(SERVO_START_POSITION);
}

/**
 * Display the cuckoo state on the screen.
 * The first line shows the time.
 * The second line shows Pac-Man related characters
 *
 * @param dateTime The current time to display on the screen.
 *                 When it is a full hour, the hour is displayed. Else, the time is displayed.
 */
void CuckooMechanism::displayCuckooState(RtcDateTime dateTime) {
    String timeString = "It's ";

    // If it is a full hour, print the hour
    if (dateTime.Minute() == 0 && dateTime.Second() == 0) {
        timeString += String(dateTime.Hour()) + " o'clock";
    } else { // Else, print the time
        const int TIME_STRING_SIZE = 6;
        char currentTimeString[TIME_STRING_SIZE];
        sprintf(currentTimeString, "%02d:%02d", dateTime.Hour(), dateTime.Minute());
        timeString += currentTimeString;
    }

    // Center timeString
    int timeStringPadding = static_cast<int>(CHARACTERS_PER_LINE - timeString.length()) / 2;
    for (int i = 0; i < timeStringPadding; i++) {
        timeString = " " + timeString;
    }

    screen->clear();
    screen->printText(timeString, 0, 0);

    // Print the following: " X ･･････････ Y " where X represents Pac-Man and Y the ghost

    // Print the Pac-Man on index 1 and the ghost on index 14
    screen->printCustomCharacter(1, 1, byte(PAC_MAN_CHARACTER));
    screen->printCustomCharacter(14, 1, byte(GHOST_CHARACTER));

    // Print the dots (from index 3 to 12)
    for (int i = 3; i < 13; ++i) {
        screen->printCustomCharacter(i, 1, byte(DOT_CHARACTER));
    }
}
