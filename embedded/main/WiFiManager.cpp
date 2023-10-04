/**
 * Implementation of the WiFiManager class.
 * This class is used to connect to the Wi-Fi network.
 */

#include "WiFiManager.h"

#include <utility>

/**
 * Constructor of the WiFiManager class
 */
WiFiManager::WiFiManager() = default;


/**
 * Initialize the Wi-Fi connection
 *
 * @param ssid      The SSID of the Wi-Fi network
 * @param password  The password of the Wi-Fi network
 */
void WiFiManager::initialize(const Screen &givenScreen, const String& ssid, const String& password) {
    this->screen = givenScreen;
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

