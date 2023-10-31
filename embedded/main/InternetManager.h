/**
 * A InternetManager object is used to connect to a Wi-Fi network.
 *
 * @author F.S. Koulen
 * @date 2023-10-02
 */

#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include "Screen.h"
#include "StateManager.h"


class InternetManager {
public:
    InternetManager();

    void initialize(Screen *givenScreen, StateManager *givenStateManager);

    void listenServer();

private:
    const int PORT = 80;
    const String ROOT = "/";
    const String LCD = "/lcd";
    const String MEASUREMENT = "/measurement";
    Screen *screen{};
    StateManager *stateManager;
    ESP8266WebServer *server;

    void handleRoot();

    void handleLCD();

    void handleMeasurement();

    void handleNotFound();
};


#endif //WIFI_MANAGER_H
