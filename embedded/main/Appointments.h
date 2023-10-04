/*
 *
 */

#ifndef APPOINTMENTS_H
#define APPOINTMENTS_H

#include "Screen.h"
#include "Constants.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "ArduinoJson.h"

class Appointments {
public:
    Appointments();

    void setScreen(Screen screen);

    void connectToAPI();

    void displayState();

    boolean displayNextAppointment();

    // No update interval needed so set to 1 minute since it will be back to time display after 15 seconds
    const int updateInterval = 60 * 1000;
private:
    Screen screen;
    DynamicJsonDocument jsonBuffer;
    JsonArray records;
    int currentAppointmentIndex = 0;

    void storeAllAppointments(String payload);
};


#endif //APPOINTMENTS_H
