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
    explicit Hygrometer(DHT sensor);

    void setScreen(Screen screen);

    float readTemperature();

    int readHumidity();

    void displayState();

    int updateInterval = 10 * 1000;

private:
    const char DEGREE_SYMBOL = (char) 223;
    DHT dht;
    Screen screen;
    DynamicJsonDocument jsonBuffer;

    void postMeasurement(float temperature, int humidity);
};


#endif //HYGROMETER_H
