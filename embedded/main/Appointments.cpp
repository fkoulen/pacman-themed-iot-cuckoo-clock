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
    httpClient.begin(client, String(BASE_URL) + API_READ_APPOINTMENTS);

    // Make the GET-request, this returns the HTTP-code.
    int httpCode = httpClient.GET();

    // Check if the response is fine.
    if (httpCode == HTTP_CODE_OK) { // HTTP_CODE_OK == 200
        Serial.println("Successfully connected to API");
        String payload = httpClient.getString();
        storeAllAppointments(payload);
        screen.printText(String(records.size()) + " " + getPluralizedAppointmentsString(), "found");
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
    if (records.size() == 0) {
        Serial.println("No appointments found");
        screen.printText("No appointments", "found");
        return;
    }

    screen.printText("Next 7 days:", String(records.size()) + " " + getPluralizedAppointmentsString());
}

/**
 * Display the next appointment on the LCD if possible
 *
 * @return whether or not there is an appointment to display
 */
boolean Appointments::displayNextAppointment() {
    if (records.size() == 0) return false;

    // If we are at the end of the list, reset the index to 0 and return false
    if (currentAppointmentIndex >= static_cast<int>(records.size())) {
        currentAppointmentIndex = 0;
        return false;
    }


    JsonObject appointment = records[currentAppointmentIndex];
    String name = appointment["name"];
    String time = appointment["start"];

    String appointmentNumber = String(currentAppointmentIndex + 1);
    Serial.print("Displaying appointment " + appointmentNumber + ": ");
    Serial.println(name + " at " + time);

    screen.printText(appointmentNumber + ": " + name, time);

    currentAppointmentIndex++;
    return true;
}

/**
 * Get the pluralized string of the word appointment
 *
 * @return The pluralized string
 */
String Appointments::getPluralizedAppointmentsString() {
    return records.size() == 1 ? "appointment" : "appointments";
}
