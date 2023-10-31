/**
 * Implementation of the Hygrometer class.
 * Contains methods to read the temperature and humidity.
 *
 * @author: F.S. Koulen
 * @date: 2023-10-02
 */

#include "Hygrometer.h"

/**
 * Constructor of the Hygrometer class.
 * Create a new Hygrometer instance and initialize the DHT sensor.
 *
 * @param pin       The pin to which the DHT sensor is connected
 * @param dhtType   The type of the DHT sensor
 */
Hygrometer::Hygrometer(DHT dht) : dht(dht), jsonBuffer(DynamicJsonDocument(JSON_BUFFER_SIZE)) {
    dht.begin();
    this->dht = dht;
}

/**
 * Set the screen to use.
 */
void Hygrometer::setScreen(Screen *givenScreen) {
    this->screen = givenScreen;
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


    if (!checkValidityOfReadings(temperature, humidity)) return;

    //  Print temperature with one decimal place and the degree symbol
    String firstLine = "Temp: " + String(temperature, 1) + DEGREE_SYMBOL + "C";
    String secondLine = "Humidity: " + String(humidity) + "%";

    screen->printText(firstLine, secondLine);
}

/**
 * Post a measurement to the API. Print the response to the serial monitor.
 * If the temperature or humidity is invalid, return 0.
 * Else, return the HTTP code of the response.
 *
 * @param temperature
 * @param humidity
 * @return The HTTP code of the response or 0 if the temperature or humidity is invalid
 */
int Hygrometer::postMeasurement() {
    float temperature = readTemperature();
    int humidity = readHumidity();

    if (!checkValidityOfReadings(temperature, humidity)) return 0;

    // Initialize a wi-fi client & http client
    WiFiClientSecure client;
    const char fingerprint[] = FINGERPRINT
    client.setFingerprint(fingerprint);
    HTTPClient httpClient;

    // Set the URL of where the call should be made to.
    httpClient.begin(client, String(BASE_URL) + API_POST_MEASUREMENT);

    // Set the content-type header
    httpClient.addHeader("Content-Type", "application/json");

    // Custom header to tell the tunnel that we don't want to see the screen
    httpClient.addHeader("X-Pinggy-No-Screen", "true");
    httpClient.addHeader("Bypass-Tunnel-Reminder", "false");

    // Create the JSON-object
    jsonBuffer.clear();
    JsonObject root = jsonBuffer.to<JsonObject>();
    root["temperature"] = temperature;
    root["humidity"] = humidity;

    // Serialize the JSON-object to a string
    String body;
    serializeJson(root, body);

    Serial.println("[HTTPS] POST... " + String(BASE_URL) + API_POST_MEASUREMENT);

    // Make the POST-request, this returns the HTTP-code.
    int httpCode = httpClient.POST(body);

    if (HTTPClient::errorToString(httpCode) == String()) { // Check if it is not an HTTPClient error
        String payload = httpClient.getString();
        jsonBuffer.clear();
        deserializeJson(jsonBuffer, payload);
        String message = jsonBuffer["message"];

        Serial.printf("[HTTPS] POST... code: %d\n", httpCode);
        if (message != "null") {
            Serial.println(message);
        } else {
            Serial.printf("[HTTPS] POST... failed, error (%d)\n", httpCode);
        }
    } else {
        Serial.printf("[HTTPS] POST... failed, error: %s\n", HTTPClient::errorToString(httpCode).c_str());
    }

    return httpCode;
}

/**
 * Check whether the temperature and humidity are valid. Display an error message if they are not.
 *
 * @param temperature The temperature to check
 * @param humidity The humidity to check
 * @return Whether the temperature and humidity are valid
 */
bool Hygrometer::checkValidityOfReadings(float temperature, int humidity) {
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        screen->printText("Failed to read", "from DHT sensor!");
        return false;
    }

    return true;
}