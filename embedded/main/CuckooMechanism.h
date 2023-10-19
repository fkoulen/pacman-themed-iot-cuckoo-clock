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
#include "Constants.h"
#include "Pitches.h"
#include "Screen.h"
#include "RtcDS1302.h"

class CuckooMechanism {
public:
    CuckooMechanism();

    void initialize(Screen *givenScreen);

    void executeCuckooMechanism(RtcDateTime time);

private:
    void playMelody();

    void moveCuckooForward();

    void moveCuckooBackward();

    void displayCuckooState(RtcDateTime dateTime);

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
            NOTE_B5, 32, NOTE_FS5, -16, NOTE_DS5, 8, NOTE_C5, 16, NOTE_C6, 16, NOTE_G6, 16, NOTE_E6, 16, NOTE_C6, 32,
            NOTE_G6, -16, NOTE_E6, 8,

            NOTE_B4, 16, NOTE_B5, 16, NOTE_FS5, 16, NOTE_DS5, 16, NOTE_B5, 32,  //2
            NOTE_FS5, -16, NOTE_DS5, 8, NOTE_DS5, 32, NOTE_E5, 32, NOTE_F5, 32, NOTE_F5, 32, NOTE_FS5, 32, NOTE_G5, 32,
            NOTE_G5, 32, NOTE_GS5, 32, NOTE_A5, 16, NOTE_B5, 8};
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
    Screen *screen{};

    byte pacMan[8] = {B01110, B11011, B11110, B11100, B11111, B01110, B00000, B00000};
    const int PAC_MAN_CHARACTER = 0;

    byte ghost[8] = {B00000, B01110, B11111, B11010, B11111, B11111, B10101, B00000,};
    const int GHOST_CHARACTER = 1;

    byte dot[8] = {B00000, B00000, B00000, B00110, B00110, B00000, B00000, B00000};
    const int DOT_CHARACTER = 2;
};


#endif //CUCKOO_MECHANISM_H
