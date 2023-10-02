/**
 * Create a WifiManager object to connect to a Wi-Fi network
 *
 * @author F.S. Koulen
 * @date 2023-10-02
 */

#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "../Screen/Screen.h"

class WiFiManager {
public:
    WiFiManager();
    void setScreen(Screen screen);
    void initializeWiFi(String ssid, String password);
private:
    Screen screen;
};


#endif //WIFI_MANAGER_H
