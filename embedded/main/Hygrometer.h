/**
 * Represents a hygrometer that measures the temperature and humidity of the air.
 * The measurements can be sent to the API and displayed on the LCD screen.
 * It uses the DHT sensor to measure the temperature and humidity.
 *
 * @author F.S. Koulen
 * @details License: GNU GPL v3
 */

#ifndef HYGROMETER_H
#define HYGROMETER_H

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <ArduinoJson.h>
#include "Screen.h"

// See `Hygrometer.cpp` for the implementation of the functions and their documentation.

class Hygrometer {
public:
    /**
     * The interval in which the state is displayed on the LCD screen, in milliseconds.
     */
    const int UPDATE_INTERVAL = 15 * 1000;

    explicit Hygrometer(DHT sensor);

    void setScreen(Screen *screen);

    void displayState();

    int postMeasurement();

private:
    /**
     * The character code of the degree symbol (°).
     */
    const char DEGREE_SYMBOL = (char) 223;
    /**
     * The DHT sensor.
     */
    DHT dht;
    /**
     * The LCD screen to use for displaying the state.
     */
    Screen *screen{};
    /**
     * The JSON buffer to use for parsing the response of the API.
     */
    DynamicJsonDocument jsonBuffer;

    float readTemperature();

    int readHumidity();

    bool checkValidityOfReadings(float temperature, int humidity);
};


#endif //HYGROMETER_H
