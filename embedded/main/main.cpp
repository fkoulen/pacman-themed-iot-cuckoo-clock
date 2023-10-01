#include <Arduino.h>
#include "Constants.h"
#include "Screen/Screen.h"
#include "WiFiManager/WiFiManager.h"

Screen screen = Screen();
WiFiManager wifiManager;

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println(); // Print empty line to separate boot messages from the rest of the output

    screen.initializeLCD();

    wifiManager = WiFiManager(screen);
    wifiManager.initializeWiFi(WIFI_SSID, WIFI_PASSWORD);
}

void loop() {

}