/**
 * Implementation of the InternetManager class.
 * This class is used to connect to the Wi-Fi network.
 */

#include "InternetManager.h"

/**
 * Constructor of the InternetManager class
 */
InternetManager::InternetManager() = default;


/**
 * Initialize the Wi-Fi connection
 *
 * @param ssid      The SSID of the Wi-Fi network
 * @param password  The password of the Wi-Fi network
 */
void InternetManager::initialize(const Screen &givenScreen, const String& ssid, const String& password) {
    this->screen = givenScreen;
    screen.printText("Initializing", "Wi-Fi connection");
    // Try to connect to the Wi-Fi network
    WiFiManager wifiManager;

    wifiManager.autoConnect(WIFI_SSID, WIFI_PASSWORD);

    Serial.println("Connected to Wi-Fi.");
    screen.printText("Connected to", "Wi-Fi.");
}

