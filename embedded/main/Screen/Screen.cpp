/**
 * Implementation of the Screen class
 *
 * @author F.S. Koulen
 * @date 2023-10-02
 */

#include "Screen.h"

Screen::Screen() {
    initializeLCD();
}

/**
 * Initialize the LCD
 */
void Screen::initializeLCD() {
    lcd.init();
    lcd.backlight();
    printText("Initializing...", "Please wait...");
}

/**
 * Clear the LCD and show the given text on the first and second line
 *
 * @param firstLine The text for the first line
 * @param secondLine The text for the second line
 */
void Screen::printText(String firstLine, String secondLine) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(firstLine);
    lcd.setCursor(0, 1);
    lcd.print(secondLine);
}