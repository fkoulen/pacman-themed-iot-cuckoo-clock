/*
 *
 */

#include "Appointments.h"

Appointments::Appointments() : jsonBuffer(DynamicJsonDocument(JSON_BUFFER_SIZE)) {
}

void Appointments::setScreen(Screen givenScreen) {
    this->screen = std::move(givenScreen);
}


/**
 * Connect to the API and store all appointments if the connection is successful.
 * If the connection is not successful, show an error message on the LCD.
 */
void Appointments::connectToAPI() {
    screen.printText("Connecting", "to API...");
    // Initialize a wi-fi client & http client
    WiFiClient client;
    HTTPClient httpClient;

    // Set the URL of where the call should be made to.
    httpClient.begin(client, API_READ_APPOINTMENTS);

    // Make the GET-request, this returns the HTTP-code.
    int httpCode = httpClient.GET();

    // Check if the response is fine.
    if (httpCode == HTTP_CODE_OK) { // HTTP_CODE_OK == 200
        Serial.println("Successfully connected to API");
        String payload = httpClient.getString();
        storeAllAppointments(payload);
        screen.printText(String(records.size()) + " appointments", "found");
    } else if (httpCode == HTTP_CODE_NOT_FOUND) {
        Serial.println("No appointments found");
        screen.printText("No appointments", "found");
    } else {
        String payload = httpClient.getString();
        deserializeJson(jsonBuffer, payload);
        String message = jsonBuffer["message"];
        screen.printText("Error ${httpCode}", message);
        Serial.println("Error " + String(httpCode));
        Serial.println(message);
    }
    delay(5000);
}

/**
 * Store all appointments in the records variable
 *
 * @param payload The JSON payload from the API
 */
void Appointments::storeAllAppointments(String payload) {
    deserializeJson(jsonBuffer, payload);
    records = jsonBuffer["records"];
}

/**
 * Display how many appointments are found on the LCD
 */
void Appointments::displayState() {
    String appointmentsPluralized = records.size() == 1 ? "appointment" : "appointments";
    screen.printText("This week:", String(records.size()) + " " + appointmentsPluralized);
}
