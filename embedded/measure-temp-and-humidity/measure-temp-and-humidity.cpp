/*
 * This snippet shows how to send a measurement of the temperature and humidity
 * to the API. It uses the KY-015 DHT11 sensor.
 *
 * @author F.S. Koulen
 * @date 2023-09-28
 */

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "main/Constants.h"

#define JSON_BUFFER_SIZE 1024

DynamicJsonDocument jsonBuffer(JSON_BUFFER_SIZE);

#define DHT_PIN 2
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

#define MEASUREMENT_INTERVAL (30 * 1000)


/**
 * Initialize the Wi-Fi connection
 */
void initializeWifi() {
    // Initialize the Serial-connection on a speed of 115200 b/s
    Serial.begin(SERIAL_BAUD_RATE);

    // Your WeMos tries to connect to your Wi-fi network
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // Keep the while-statement alive as long as we are NOT connected
    // to the Wi-fi network.
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }
}

/*
 * Post a measurement of the temperature and humidity to the API.
 *
 * @param temperature The temperature to post
 * @param humidity The humidity to post
 */
void postMeasurement(float temperature, float humidity) {
    // Initialize a wi-fi client & http client
    WiFiClient client;
    HTTPClient httpClient;

    // Set the URL of where the call should be made to.
    httpClient.begin(client, String(BASE_URL) + API_POST_MEASUREMENT);

    // Set the content-type header
    httpClient.addHeader("Content-Type", "application/json");

    // Custom header to tell the Pinggy that we don't want to see the screen
    httpClient.addHeader("X-Pinggy-No-Screen", "true");

    // Create the JSON-object
    jsonBuffer.clear();
    JsonObject root = jsonBuffer.to<JsonObject>();
    root["temperature"] = temperature;
    root["humidity"] = humidity;

    // Serialize the JSON-object to a string
    String body;
    serializeJson(root, body);
    Serial.println(body);

    // Make the POST-request, this returns the HTTP-code.
    int httpCode = httpClient.POST(body);

    // Check if the response is fine.
    if (httpCode == HTTP_CODE_CREATED) { // HTTP_CODE_OK == 200
        Serial.println("Measurement created");
    } else if (httpCode == HTTP_CODE_BAD_REQUEST) {
        Serial.println("Bad request");
    } else {
        Serial.println("Something went wrong");
        Serial.println(httpCode);
        Serial.println(httpClient.getString());
    }
}


void setup() {
    initializeWifi();
    // Start with measuring
    dht.begin();
}

void loop() {
    // Measure current temperature and humidity
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // If one of the values is NaN, skip this measurement
    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Error reading the sensor");
        return;
    }


    postMeasurement(temperature, humidity);

    // Pause between measurements
    delay(MEASUREMENT_INTERVAL);
}