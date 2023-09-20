#include <Arduino.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for 16 chars and 2 line display

void initializeLCD() {
    lcd.init();         // Initialize the LCD
    lcd.backlight();    // Turn on the backlight
}

void setup() {
    initializeLCD();
}

void loop() {

}