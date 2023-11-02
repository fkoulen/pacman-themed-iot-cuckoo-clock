/**
 * Represents the screen of the device.
 * This class is responsible for printing text on the screen and creating custom characters.
 *
 * @author F.S. Koulen
 * @details License: GNU GPLv3
 */

#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Constants.h"

// See `Screen.cpp` for the implementation of the functions and their documentation.

class Screen {
public:
    Screen();

    void initializeLCD();

    void printCustomCharacter(int position, int row, int character);

    void printText(const String &line, unsigned int positionLine, unsigned int row);

    void printText(const String &firstLine, unsigned int positionFirstLine, const String &secondLine,
                   unsigned int positionSecondLine, bool clear);

    void printText(const String &firstLine, const String &secondLine);

    void createCustomCharacter(int location, byte pixels[]);

    void clear();

    bool toggleBacklight();

    bool isBacklightOn() const;

private:
    /**
     * The LCD object used to print text on the screen.
     */
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(LCD_ADDRESS, CHARACTERS_PER_LINE, NUMBER_OF_LINES);

    /**
     * Whether the backlight is on or off.
     */
    bool backlightOn = false;

    void setBacklightOn(bool turnOn);

};

#endif //SCREEN_H
