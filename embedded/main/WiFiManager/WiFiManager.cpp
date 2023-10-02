/**
 * Implementation of the WiFiManager class.
 * This class is used to connect to the Wi-Fi network.
 */

#include "WiFiManager.h"

/**
 * Constructor of the WiFiManager class
 */
WiFiManager::WiFiManager() {}

/**
 * Set the screen to be used by the WiFiManager
 *
 * @param givenScreen The screen object
 */
void WiFiManager::setScreen(Screen givenScreen) {
    this->screen = givenScreen;
}

/**
 * Initialize the Wi-Fi connection
 *
 * @param ssid      The SSID of the Wi-Fi network
 * @param password  The password of the Wi-Fi network
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

