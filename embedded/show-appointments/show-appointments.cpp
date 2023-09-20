#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>

#define WIFI_SSID      "iotroam"
#define WIFI_PASSWORD  "OQqcD8LpM7"

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for 16 chars and 2 line display

/**
 * Initialize the LCD
 */
void initializeLCD() {
    lcd.init();         // Initialize the LCD
    lcd.backlight();    // Turn on the backlight
}

/**
 * Clear the LCD and show the given text on the first and second line
 *
 * @param firstLine The text for the first line
 * @param secondLine The text for the second line
 */
void showText(String firstLine, String secondLine) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(firstLine);
    lcd.setCursor(0, 1);
    lcd.print(secondLine);
}

/**
 * Initialize the Wi-Fi connection
 */
void initializeWifi() {
    showText("Connecting", "to Wi-Fi...");
    // Initialize the Serial-connection on a speed of 115200 b/s
    Serial.begin(115200);

    // Your WeMos tries to connect to your Wi-fi network
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // Keep the while-statement alive as long as we are NOT connected
    // to the Wi-fi network.
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }
}

void setup() {
    initializeLCD();
    initializeWifi();
    showText("Connected", "to Wi-Fi");
}

void loop() {

}