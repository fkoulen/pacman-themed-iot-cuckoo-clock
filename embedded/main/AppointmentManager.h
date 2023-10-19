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
#include "TimeManager.h"

class AppointmentManager {
public:
    AppointmentManager();

    void setScreen(Screen *screen);

    void connectToAPI();

    void displayState();

    boolean displayNextAppointment(TimeManager timeManager);

    // No update interval needed so set to 1 minute since it will be back to time display after 15 seconds
    const int UPDATE_INTERVAL = 60 * 1000;
private:
    Screen *screen{};
    DynamicJsonDocument jsonBuffer;
    JsonArray records;
    int currentAppointmentIndex = 0;

    void storeAllAppointments(String payload);
    String getPluralizedAppointmentsString();
};


#endif //APPOINTMENTS_H
