/**
 * A Hygrometer object is used to measure the temperature and humidity.
 */

#ifndef HYGROMETER_H
#define HYGROMETER_H

#include <Arduino.h>
#include "Adafruit_Sensor.h"
#include "DHT.h"
#include "Screen.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "ArduinoJson.h"


class Hygrometer {
public:
    const int UPDATE_INTERVAL = 15 * 1000;

    explicit Hygrometer(DHT sensor);

    void setScreen(Screen *screen);

    float readTemperature();

    int readHumidity();

    void displayState();

    int postMeasurement();

private:
    const char DEGREE_SYMBOL = (char) 223;
    DHT dht;
    Screen *screen{};
    DynamicJsonDocument jsonBuffer;

    bool checkValidityOfReadings(float temperature, int humidity);
};


#endif //HYGROMETER_H
