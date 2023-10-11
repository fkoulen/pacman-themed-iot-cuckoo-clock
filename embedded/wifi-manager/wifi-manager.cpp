#include <Arduino.h>
#include <WiFiManager.h>
#include "main/Constants.h"

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);

    WiFiManager wifiManager;

    wifiManager.autoConnect(WIFI_SSID, WIFI_PASSWORD);

    // Code only gets here if the Wi-Fi connection was successful
    Serial.println("Connected to Wi-Fi.");
}

void loop() {
}