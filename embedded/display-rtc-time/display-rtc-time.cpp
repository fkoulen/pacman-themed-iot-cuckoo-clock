/**
* Display the time from the RTC on the LCD.
 *
 * @author F.S. Koulen
 * @date 2023-09-27
*/

#include <Arduino.h>
#include <Wire.h>                   // for I2C communication
#include <LiquidCrystal_I2C.h>      // for LCD
#include <RtcDS1302.h>              // for RTC

#define SERIAL_BAUD_RATE 57600

#define LCD_UPDATE_INTERVAL 1000

#define LCD_ADDRESS 0x27
#define CHARACTERS_PER_LINE 16
#define NUMBER_OF_LINES 2
LiquidCrystal_I2C lcd(LCD_ADDRESS, CHARACTERS_PER_LINE, NUMBER_OF_LINES);

#define RTC_CLK_PIN 15
#define RTC_DAT_PIN 13
#define RTC_RST_PIN 12
ThreeWire wiring(RTC_DAT_PIN, RTC_CLK_PIN, RTC_RST_PIN);
RtcDS1302<ThreeWire> Rtc(wiring); // Create RTC with the provided wiring


#define countOf(a) (sizeof(a) / sizeof(a[0])) // countOf is a macro that returns the number of elements in an array

/**
 * Display the date and time on the LCD.
 */
void displayDateTime() {
    RtcDateTime now = Rtc.GetDateTime();

    if (!now.IsValid()) {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
    }

    char dateString[CHARACTERS_PER_LINE];
    char timeString[CHARACTERS_PER_LINE];

    // Print Date
    lcd.setCursor(0, 0);
    sprintf(dateString, "Date: %02u/%02u/%04u", now.Day(), now.Month(), now.Year());
    lcd.print(dateString);

    // Print Time
    lcd.setCursor(0, 1);
    sprintf(timeString, "Time: %02d:%02d:%02d", now.Hour(), now.Minute(), now.Second());
    lcd.print(timeString);
}

/*
 * Initialize the LCD.
 */
void initializeLCD() {
    lcd.init();
    lcd.backlight();
}

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
}


void loop() {
    displayDateTime();

    delay(LCD_UPDATE_INTERVAL);
}
