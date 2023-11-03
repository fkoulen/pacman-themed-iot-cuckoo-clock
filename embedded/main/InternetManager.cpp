/**
 * Implementation of the InternetManager class.
 * Has methods to handle the internet connection, to set up a web server, and to handle requests.
 * The server can be used to control the LCD backlight and to get the current measurement.
 *
 * @author F.S. Koulen
 * @details License: GNU GPLv3
 * <br/>
 */

#include "InternetManager.h"

/**
 * Constructor of the InternetManager class.
 * Initializes the JSON buffer and the server.
 */
InternetManager::InternetManager() : jsonBuffer(DynamicJsonDocument(JSON_BUFFER_SIZE)) {
}

/**
 * Initialize the Wi-Fi connection and set up the web server.
 *
 * @param givenScreen   The screen to use for displaying messages.
 * @param givenStateManager    The state manager to use for posting the current measurement.
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


    // Configure the time for certificate validation
    configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
//
//    server->on(ROOT, HTTP_GET, [this] { handleRedirectToHTTPS(); });
//    server->begin();

//    Serial.println("HTTP server started. Accessible via http://" + WiFi.localIP().toString());
    secureServer->getServer().setRSACert(new X509List(serverCert), new PrivateKey(serverKey));

    // Cache SSL sessions to accelerate the TLS handshake.
//    secureServer->getServer().setCache(cache);

    secureServer->on(ROOT, HTTP_GET, [this] { handleRoot(); });
    secureServer->on(LCD, HTTP_POST, [this] { handleLCD(); });
    secureServer->on(MEASUREMENT, HTTP_GET, [this] { handleMeasurement(); });
    secureServer->onNotFound([this] { handleNotFound(); });
    secureServer->enableCORS(true);
    secureServer->begin();
    Serial.println("Server started. Accessible via https://" + WiFi.localIP().toString());
}

/**
 * Listen for requests to the server.
 * This method should be called in the loop.
 */
void InternetManager::listenServer() {
//    server->handleClient();
    secureServer->handleClient();
    MDNS.update();
}


void InternetManager::handleRedirectToHTTPS() {
    Serial.println("[HTTPServer] Handling redirect to HTTPS server");
    secureServer->sendHeader("Location", String("https://") + WiFi.localIP().toString(), true);
    secureServer->send(HTTP_CODE_MOVED_PERMANENTLY, "text/plain", "");
}

/**
 * Handle the GET request to the root URI.
 * This method is called when the root URI is requested.
 * It sends a response that describes that this is the URL for the web server of the WEMOS.
 */
void InternetManager::handleRoot() {
    Serial.println("[HTTPSServer] Handling root request");
    secureServer->send(HTTP_CODE_OK, "text/html", "<p>This is the URL for the web server of the WEMOS.</p>");
}

/**
 * Handle the POST request to toggle the LCD backlight.
 * This method is called when the LCD URI is requested.
 * It toggles the backlight and sends a response that describes that the backlight is turned on or off.
 */
void InternetManager::handleLCD() {
    Serial.println("[HTTPSServer] Handling LCD request");
    bool backlightOn = screen->toggleBacklight();
    backlightOn ? stateManager->displayTime() : screen->clear();
    secureServer->send(HTTP_CODE_OK, "text/plain", "Turned backlight " + String(backlightOn ? "on" : "off") + ".");
}

/**
 * Handle the GET request to post a measurement.
 * This method is called when the measurement URI is requested.
 * It posts the current measurement and sends a response that describes the result of the request.
 */
void InternetManager::handleMeasurement() {
    jsonBuffer.clear();
    Serial.println("[HTTPSServer] Handling measurement request");
    int responseCode = stateManager->postMeasurement();
    jsonBuffer["response"] = responseCode;
    String response;
    serializeJson(jsonBuffer, response);
    secureServer->send(HTTP_CODE_OK, "application/json", response);
}

/**
 * Handle the request to an unknown URI.
 * This method is called when an unknown URI is requested.
 * It sends a response that describes that the requested URI is not found.
 */
void InternetManager::handleNotFound() {
    Serial.println("[HTTPSServer] Handling unknown request");
    secureServer->send(HTTP_CODE_OK, "text/plain", "404: Not found");
}