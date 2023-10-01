#include "WiFiManager.h"

WiFiManager::WiFiManager() {}

WiFiManager::WiFiManager(Screen screen) {
    this->screen = screen;
}


/**
 * Initialize the WiFi connection
 */
void WiFiManager::initializeWiFi(String ssid, String password) {
    screen.printText("Connecting to", "Wi-Fi...");
    // Try to connect to the Wi-Fi network
    WiFi.begin(ssid, password);

    // Prevent the code from continuing as long as we are not connected
    while (WiFi.status() != WL_CONNECTED) {

        Serial.println("Attempting to connect to SSID: " + String(WIFI_SSID));
        delay(1000);
    }

    Serial.println("Connected to Wi-Fi.");
    screen.printText("Connected to", "Wi-Fi.");
}

