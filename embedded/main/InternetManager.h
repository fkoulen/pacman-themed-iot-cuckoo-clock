/**
 * Represents a manager that handles the internet connection and sets up a web server.
 * The server can be used to control the LCD backlight and to get the current measurement.
 * The screen is used to display messages. The state manager is used to post the current measurement.
 *
 * @author F.S. Koulen
 * @details License: GNU GPLv3
 */

#ifndef INTERNET_MANAGER_H
#define INTERNET_MANAGER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WebServerSecure.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>
#include "Screen.h"
#include "StateManager.h"
#include "HTTPSClient.h"

// See `InternetManager.cpp` for the implementation of the functions and their documentation.

class InternetManager {
public:
    InternetManager();

    void initialize(Screen *givenScreen, StateManager *givenStateManager);

    void listenServer();

private:
    /**
     * Port of the web server.
     */
    const int PORT = 443;
    /**
     * Path to the root URI.
     */
    const String ROOT = "/";
    /**
     * Path to the URI for controlling the LCD backlight.
     */
    const String LCD = "/lcd";
    /**
     * Path to the URI for requesting the current measurement to be posted.
     */
    const String MEASUREMENT = "/measurement";
    /**
     * Screen to use for displaying messages.
     */
    Screen *screen{};
    /**
     * State manager to use for posting the current measurement.
     */
    StateManager *stateManager{};
    /**
     * Server to use for setting up the web server and handling requests.
     */
    ESP8266WebServerSecure *secureServer = new ESP8266WebServerSecure(PORT);
    ESP8266WebServer *server = new ESP8266WebServer(80);
    /**
     * Create cache for server
     */
     ServerSessions *cache = new ServerSessions(5);
    /**
     * The JSON buffer to use for parsing the response of the API.
     */
    DynamicJsonDocument jsonBuffer;

    void handleRedirectToHTTPS();

    void handleRoot();

    void handleLCD();

    void handleMeasurement();

    void handleNotFound();
};


#endif //INTERNET_MANAGER_H
