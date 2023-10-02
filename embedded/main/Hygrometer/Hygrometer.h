/**
 * Create a hygrometer to measure the temperature and humidity.
 */

#ifndef HYGROMETER_H
#define HYGROMETER_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "../Screen/Screen.h"

class Hygrometer {
public:
    explicit Hygrometer(DHT sensor);

    void setScreen(Screen screen);

    float readTemperature();

    int readHumidity();

    void displayState();

private:
    DHT dht;
    Screen screen;
    int interval = 10 * 1000;
};


#endif //HYGROMETER_H
