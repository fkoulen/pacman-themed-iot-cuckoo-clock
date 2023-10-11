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
#include "Screen.h"
#include <WiFiManager.h>

class InternetManager {
public:
    InternetManager();

    void initialize(const Screen &givenScreen, const String &ssid, const String &password);

private:
    Screen screen;
};


#endif //WIFI_MANAGER_H
