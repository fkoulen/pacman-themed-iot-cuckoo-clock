/**
 * Implementation of the InternetManager class.
 * This class is used to connect to the Wi-Fi network.
 */

#include "InternetManager.h"

/**
 * Constructor of the InternetManager class
 */
InternetManager::InternetManager() {
    server = new ESP8266WebServer(PORT);
}

/**
 * Initialize the Wi-Fi connection
 *
 * @param givenScreen   The screen to use
 */
void InternetManager::initialize(Screen *givenScreen, StateManager *givenStateManager) {
    this->screen = givenScreen;
    this->stateManager = givenStateManager;
    screen->printText("Initializing", "Wi-Fi connection");
    // Try to connect to the Wi-Fi network
    WiFiManager wifiManager;

    wifiManager.autoConnect(WIFI_SSID, WIFI_PASSWORD);

    Serial.println("Connected to Wi-Fi.");
    screen->printText("Connected to", "Wi-Fi.");
    delay(TIME_TO_SHOW_MESSAGE);
    screen->printText("Starting server:", WiFi.localIP().toString());
    delay(TIME_TO_SHOW_MESSAGE);
    server->on(ROOT, HTTP_GET, [this] { handleRoot(); });
    server->on(LCD, HTTP_POST, [this] { handleLCD(); });
    server->onNotFound([this] { handleNotFound(); });
    server->begin();
    Serial.println("Server started.");
}

/**
 * Handle the server
 */
void InternetManager::listenServer() {
    server->handleClient();
}

/**
 * Handle the GET request to the root URI
 */
void InternetManager::handleRoot() {
    Serial.println("[Server] Handling root request");
    server->send(HTTP_CODE_OK, "text/html", "<p>This is the URL for the web server of the WEMOS.</p>");
}

/**
 * Handle the POST request to toggle the LCD backlight
 */
void InternetManager::handleLCD() {
    Serial.println("[Server] Handling LCD request");
    bool backlightOn = screen->toggleBacklight();
    backlightOn ? stateManager->displayTime() : screen->clear();
    server->send(HTTP_CODE_OK, "text/plain", "Turned backlight " + String(backlightOn ? "on" : "off") + ".");
}

/**
 * Handle the request to an unknown URI
 */
void InternetManager::handleNotFound() {
    Serial.println("[Server] Handling unknown request");
    server->send(HTTP_CODE_NOT_FOUND, "text/plain", "404: Not found");
}