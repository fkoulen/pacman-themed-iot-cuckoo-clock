/**
 * Create a hygrometer to measure the temperature and humidity.
 */

#ifndef HYGROMETER_H
#define HYGROMETER_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "../Screen/Screen.h"
#include "../main.h"


class Hygrometer {
public:
    explicit Hygrometer(DHT sensor);

    void setScreen(Screen screen);

    float readTemperature();

    int readHumidity();

    void displayState();

    int updateInterval = 10 * 1000;

private:
    DHT dht;
    Screen screen;
};


#endif //HYGROMETER_H
