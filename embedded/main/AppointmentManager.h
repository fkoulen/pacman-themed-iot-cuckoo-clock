/**
 * The AppointmentManager class is responsible for fetching, storing and displaying appointments.
 * It uses the Screen class to display the appointments on the LCD.
 *
 * @author F.S. Koulen
 * @license GNU GPLv3
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

    void fetch();

    void displayState();

    boolean displayNextAppointment(TimeManager timeManager);

    /**
     * The update interval for when the screen should be updated. It is set to 1 minute since the display will be back
     * to the time display after 15 seconds. This means that the appointment will be displayed for 15 seconds at most
     * and the screen does not need to be updated more often than that.
     */
    const int UPDATE_INTERVAL = 60 * 1000;
private:
    Screen *screen{}; // Pointer to the screen to use for displaying the appointments
    DynamicJsonDocument jsonBuffer; // Buffer to store the JSON response in
    JsonArray records; // Array to store the appointments in
    int currentAppointmentIndex = 0; // Index of the current appointment to display

    void storeAllAppointments(String payload);
    String getPluralizedAppointmentsString();
};


#endif //APPOINTMENTS_H
