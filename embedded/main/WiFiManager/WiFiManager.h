#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "../Screen/Screen.h"

class WiFiManager {
public:
    WiFiManager();
    explicit WiFiManager(Screen screen);
    void initializeWiFi(String ssid, String password);
private:
    Screen screen;
};


#endif //WIFI_MANAGER_H
