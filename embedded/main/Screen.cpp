/**
 * Implementation of the Screen class.
 * This class is used to control the LCD.
 * It contains methods to initialize the LCD and to print text on the LCD.
 *
 * @author F.S. Koulen
 * @details License: GNU GPLv3
 * <br/>
 */

#include "Screen.h"

/**
 * Constructor for the Screen class.
 * This constructor is empty because the LCD is initialized in the `initializeLCD` method.
 */
Screen::Screen() = default;

/**
 * Initialize the LCD and turn on the backlight
 */
void Screen::initializeLCD() {
    Serial.println("Initializing LCD...");
    lcd.init();
    setBacklightOn(true);
    printText("Initializing...", "Please wait...");
    Serial.println("LCD initialized.");
}

/**
 * Print a custom character on the given location and row
 *
 * @param position The position for the character
 * @param row The row for the character
 * @param character The character to print
 */
void Screen::printCustomCharacter(int position, int row, int character) {
    lcd.setCursor(position, row);
    lcd.write(character);
}


/**
 * Print the given text on the given line and row
 *
 * @param line The text to print
 * @param positionLine The position for the text
 * @param row The row for the text
 * @param clear Whether to clear the LCD before printing the text
 */
void Screen::printText(const String &line, unsigned int positionLine, unsigned int row) {
    if (!backlightOn) return;
    lcd.setCursor(positionLine, row);
    lcd.print(line);
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
                       unsigned int positionSecondLine, bool clear = false) {
    if (clear) lcd.clear();

    printText(firstLine, positionFirstLine, 0);
    printText(secondLine, positionSecondLine, 1);
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

/**
 * Create a custom character on the given location with the character pixels
 *
 * @param location The location of the custom character
 * @param pixels The character's pixels
 */
void Screen::createCustomCharacter(int location, byte pixels[]) {
    lcd.createChar(location, pixels);
}

/**
 * Toggle the backlight
 *
 * @return Whether the backlight is now on or off
 */
bool Screen::toggleBacklight() {
    setBacklightOn(!backlightOn);

    return backlightOn;
}

/**
 * Check whether the backlight is on
 *
 * @return Whether the backlight is on
 */
bool Screen::isBacklightOn() const {
    return backlightOn;
}

/**
 * Set the backlight
 *
 * @param backlightOn Whether to turn the backlight on or off
 */
void Screen::setBacklightOn(bool turnOn) {
    this->backlightOn = turnOn;
    lcd.clear();
    Serial.println("Turning screen " + String(backlightOn ? "on" : "off") + "...");
    backlightOn ? lcd.backlight() : lcd.noBacklight();
}
