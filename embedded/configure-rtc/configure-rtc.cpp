/**
 * Set the time of the RTC module by retrieving it from the NTP server.
 *
 * @author F.S. Koulen
 * @date 2023-10-07
 */
#include <Arduino.h>
#include <ezTime.h>
#include <RtcDS1302.h>
#include <LiquidCrystal_I2C.h>
#include "main/Constants.h"
#include <ESP8266WiFi.h>

LiquidCrystal_I2C lcd(LCD_ADDRESS, CHARACTERS_PER_LINE,
                      NUMBER_OF_LINES); // create LCD with I2C address 0x27, 16 characters per line, 2 lines
ThreeWire myWire(RTC_DAT_PIN, RTC_CLK_PIN, RTC_RST_PIN); // IO (DAT), SCL (CLK), CE (RST)
RtcDS1302<ThreeWire> RTC(myWire);


void setup() {
    lcd.init();
    lcd.backlight();
    lcd.home();
    lcd.print("Connecting to");
    lcd.setCursor(0, 1);
    lcd.print("Wi-Fi...");
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println(); // Print empty line to separate boot messages from the rest of the output
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }

    lcd.clear();
    lcd.home();
    lcd.print("Retrieving time");
    lcd.setCursor(0, 1);
    lcd.print("from NTP server...");

    setDebug(INFO); // Enable debug output to serial
    waitForSync(); // Block until clock is in sync

    Serial.println("UTC:             " + UTC.dateTime());

    Timezone timeZone;
    timeZone.setLocation(TIME_ZONE);

    Serial.println("Local time:             " + timeZone.dateTime());

    lcd.clear();
    lcd.home();
    lcd.print("Configuring RTC");
    lcd.setCursor(0, 1);
    lcd.print("with NTP time...");

    RTC.Begin();
    RTC.SetIsWriteProtected(false); // Unlock RTC for writing
    RTC.SetIsRunning(true); // Enable RTC

    RTC.SetDateTime(RtcDateTime(timeZone.year(), timeZone.month(), timeZone.day(), timeZone.hour(), timeZone.minute(),
                                timeZone.second())); // Set RTC time to NTP time

    RTC.SetIsWriteProtected(true); // Lock RTC for writing
}

void loop() {
    const RtcDateTime dateTime = RTC.GetDateTime();


    char dateString[CHARACTERS_PER_LINE];
    char timeString[CHARACTERS_PER_LINE];

    sprintf(dateString, "%02u/%02u/%04u", dateTime.Day(), dateTime.Month(), dateTime.Year());

    sprintf(timeString, "%02d:%02d:%02d", dateTime.Hour(), dateTime.Minute(), dateTime.Second());

    lcd.clear();
    lcd.home();
    lcd.print(dateString);
    lcd.setCursor(0, 1);
    lcd.print(timeString);

    delay(1000);
}
