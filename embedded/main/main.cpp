#include <Arduino.h>
#include "Constants.h"
#include "Screen/Screen.h"
#include "WiFiManager/WiFiManager.h"
#include "TimeManager/TimeManager.h"
#include "Hygrometer/Hygrometer.h"

Screen screen = Screen();
WiFiManager wifiManager;
ThreeWire rtcWiring(RTC_DAT_PIN, RTC_CLK_PIN, RTC_RST_PIN);
TimeManager timeManager = TimeManager(rtcWiring);
DHT dht(DHT_PIN, DHT_TYPE);
Hygrometer hygrometer = Hygrometer(dht);

int currentDisplay = 0;
const int MAX_DISPLAYS = 2;

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println(); // Print empty line to separate boot messages from the rest of the output

    screen.initializeLCD();
    wifiManager.setScreen(screen);
    timeManager.setScreen(screen);
    hygrometer.setScreen(screen);

//    wifiManager.initializeWiFi(WIFI_SSID, WIFI_PASSWORD);

}

void loop() {
//    if (currentDisplay == 1) {
//        timeManager.displayTime();
//    } else if (currentDisplay == 0) {
        hygrometer.displayState();
//    }
}