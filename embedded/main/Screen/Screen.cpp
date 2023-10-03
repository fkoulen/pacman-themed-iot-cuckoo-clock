/**
 * Implementation of the Screen class. This class is used to control the LCD.
 * It contains methods to initialize the LCD and to print text on the LCD.
 *
 * @author F.S. Koulen
 * @date 2023-10-02
 */

#include "Screen.h"

Screen::Screen() = default;

/**
 * Initialize the LCD
 */
void Screen::initializeLCD() {
    Serial.println("Initializing LCD...");
    lcd.init();
    lcd.backlight();
    printText("Initializing...", "Please wait...");
    Serial.println("LCD initialized.");
}

/**
 * Clear the LCD if specified and show the given text on the first and second line
 *
 * @param clear Whether to clear the LCD before printing the text
 * @param firstLine The text for the first line
 * @param positionFirstLine The position for the first line
 * @param secondLine The text for the second line
 * @param positionSecondLine The position for the second line
 */
void Screen::printText(const String &firstLine, unsigned int positionFirstLine, const String &secondLine,
                       unsigned int positionSecondLine, bool clear = true) {
    if (clear) lcd.clear();

    lcd.setCursor(positionFirstLine, 0);
    lcd.print(firstLine);
    lcd.setCursor(positionSecondLine, 1);
    lcd.print(secondLine);
}


/**
 * Clear the LCD and show the given text on the first and second line
 *
 * @param firstLine The text for the first line
 * @param secondLine The text for the second line
 */
void Screen::printText(const String &firstLine, const String &secondLine) {
    printText(firstLine, 0, secondLine, 0, true);
}

/**
 * Clear the LCD
 */
void Screen::clear() {
    lcd.clear();
}