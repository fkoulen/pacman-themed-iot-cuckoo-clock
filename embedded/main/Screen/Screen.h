/**
 * Create a Screen object to print text on the LCD screen.
 *
 */
#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include "../constants.h"
#include "LiquidCrystal_I2C.h"

class Screen {
    public:
        Screen();
        void initializeLCD();
        void printText(String firstLine, String secondLine);
    private:
        LiquidCrystal_I2C lcd = LiquidCrystal_I2C(LCD_ADDRESS, 16, 2);
};

#endif //SCREEN_H
