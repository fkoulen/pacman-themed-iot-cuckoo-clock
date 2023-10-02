#include <Arduino.h>
#include "Constants.h"
#include "Screen/Screen.h"
#include "WiFiManager/WiFiManager.h"
#include "TimeManager/TimeManager.h"

Screen screen = Screen();
WiFiManager wifiManager;
ThreeWire rtcWiring(RTC_DAT_PIN, RTC_CLK_PIN, RTC_RST_PIN);
TimeManager timeManager = TimeManager(rtcWiring);

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println(); // Print empty line to separate boot messages from the rest of the output

    screen.initializeLCD();

    wifiManager.setScreen(screen);
    wifiManager.initializeWiFi(WIFI_SSID, WIFI_PASSWORD);

    timeManager.setScreen(screen);
}

void loop() {
    timeManager.displayTime();
}