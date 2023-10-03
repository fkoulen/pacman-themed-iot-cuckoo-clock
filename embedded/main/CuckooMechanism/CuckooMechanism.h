/**
 * Use a CuckooMechanism object to play the melody or move the cuckoo.
 *
 * @author Robson Couto
 * @see https://github.com/robsoncouto/arduino-songs/blob/master/pacman/pacman.ino
 * @editor F.S. Koulen
 * @date 2023-10-03
 */


#ifndef CUCKOO_MECHANISM_H
#define CUCKOO_MECHANISM_H

#include <Arduino.h>
#include <Servo.h>
#include "../Constants.h"
#include "../Pitches.h"

class CuckooMechanism {
public:
    CuckooMechanism();

    void initialize();

    void moveCuckooAndPlayMelody();

private:
    void playMelody();

    void moveCuckooForward();

    void moveCuckooBackward();

    static const int BPM = 105;
    static const int MELODY_SIZE = 62;
    /**
     * Notes of the melody followed by the duration.
     * A 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on.
     * Negative numbers are used to represent dotted notes,
     * so -4 means a dotted quarter note, that is, a quarter plus an eighteenth.
     */
    int melody[MELODY_SIZE] = {

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
    Servo motor;
};


#endif //CUCKOO_MECHANISM_H
