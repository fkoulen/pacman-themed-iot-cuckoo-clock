/*
 * Show Current Time
 * 
 * This sketch receives the current time and date from the computer and displays it on an LCD.
 * 
 * @author: F.S. Koulen
 * @license MIT
 */


#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

const int DATETIME_LENGTH = 19;
const int END_TIME = 8;
const int START_TIME = 9;
const char *const DATE_PREFIX = "Date: ";
const char *const TIME_PREFIX = "Time: ";
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
    Serial.begin(9600); // Initialize serial communication
    lcd.init();         // Initialize the LCD
    lcd.backlight();    // Turn on the backlight
    lcd.setCursor(0, 0);
    lcd.print(DATE_PREFIX);
    lcd.setCursor(0, 1);
    lcd.print(TIME_PREFIX);
}

void loop() {
    if (Serial.available() >= DATETIME_LENGTH) { // Wait for 19 characters (time and date string)
        String dateTimeString = Serial.readStringUntil('\n'); // Read the incoming data
        String time = dateTimeString.substring(0, END_TIME); // Extract time substring
        String date = dateTimeString.substring(START_TIME, DATETIME_LENGTH); // Extract date substring
        lcd.setCursor(strlen(DATE_PREFIX), 0);
        lcd.print(date); // Display the received date
        lcd.setCursor(strlen(TIME_PREFIX), 1);
        lcd.print(time); // Display the received time
    }
}
