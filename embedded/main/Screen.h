/**
 * A Screen object is used to print text on the LCD screen.
 *
 * @author F.S. Koulen
 * @date 2023-10-02
 */

#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include "Constants.h"
#include "LiquidCrystal_I2C.h"

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
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(LCD_ADDRESS, CHARACTERS_PER_LINE, NUMBER_OF_LINES);
    bool backlightOn = false;

    void setBacklightOn(bool turnOn);

};

#endif //SCREEN_H
