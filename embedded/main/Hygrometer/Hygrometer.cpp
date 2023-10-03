/**
 * Implementation of the Hygrometer class.
 * Contains methods to read the temperature and humidity.
 *
 * @author: F.S. Koulen
 * @date: 2023-10-02
 */

#include "Hygrometer.h"

#include <utility>

/**
 * Constructor of the Hygrometer class.
 * Create a new Hygrometer instance and initialize the DHT sensor.
 *
 * @param pin       The pin to which the DHT sensor is connected
 * @param dhtType   The type of the DHT sensor
 */
Hygrometer::Hygrometer(DHT dht) : dht(dht) {
    dht.begin();
}

/**
 * Set the screen to use.
 */
void Hygrometer::setScreen(Screen givenScreen) {
    this->screen = std::move(givenScreen);
}

/**
 * Read the temperature from the DHT sensor.
 *
 * @return The temperature in degrees Celsius with one decimal place
 */
float Hygrometer::readTemperature() {
    return dht.readTemperature();
}

/**
 * Read the humidity from the DHT sensor.
 *
 * @return The humidity in percent
 */
int Hygrometer::readHumidity() {
    return static_cast<int>(dht.readHumidity());
}

/**
 * Display the current state of the DHT sensor on the LCD screen.
 */
void Hygrometer::displayState() {
    float temperature = readTemperature();
    int humidity = readHumidity();


    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        screen.printText("Failed to read", "from DHT sensor!");
        return;
    }

    //  Print temperature with one decimal place and the degree symbol
    String firstLine = "Temp: " + String(temperature, 1) + (char) 223 + "C";
    String secondLine = "Humidity: " + String(humidity) + "%";

    screen.printText(firstLine, secondLine);
}