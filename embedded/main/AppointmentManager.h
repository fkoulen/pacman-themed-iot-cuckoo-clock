/**
 * Represents an appointment manager that is responsible for fetching, storing and displaying appointments.
 * It uses the Screen class to display the appointments on the LCD.
 * The appointments are fetched from the API and stored in a JSON array.
 *
 * @author F.S. Koulen
 * @details License: GNU GPLv3
 */

#ifndef APPOINTMENTS_H
#define APPOINTMENTS_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "Screen.h"
#include "Constants.h"
#include "TimeManager.h"

// See `AppointmentManager.cpp` for the implementation of the functions and their documentation.

class AppointmentManager {
public:
    AppointmentManager();

    void setScreen(Screen *screen);

    void fetch();

    void displayState();

    bool displayNextAppointment(TimeManager timeManager);

    /**
     * The update interval for when the screen should be updated. It is set to 1 minute since the display will be back
     * to the time display after 15 seconds. This means that the appointment will be displayed for 15 seconds at most
     * and the screen does not need to be updated more often than that.
     */
    const int UPDATE_INTERVAL = 60 * 1000;
private:
    /**
     * Pointer to the screen to use for displaying the appointments
     */
    Screen *screen{};
    /**
     * Buffer to store the JSON response in
     */
    DynamicJsonDocument jsonBuffer;
    /**
     * Array to store the appointments in
     */
    JsonArray records;
    /**
     * The index of the current appointment to display
     */
    int currentAppointmentIndex = 0;

    void storeAllAppointments(String payload);

    String getPluralizedAppointmentsString();
};


#endif //APPOINTMENTS_H
