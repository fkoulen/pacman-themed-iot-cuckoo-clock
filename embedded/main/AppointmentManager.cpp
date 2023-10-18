/*
 *
 */

#include "AppointmentManager.h"

AppointmentManager::AppointmentManager() : jsonBuffer(DynamicJsonDocument(JSON_BUFFER_SIZE)) {
}

void AppointmentManager::setScreen(Screen givenScreen) {
    this->screen = std::move(givenScreen);
}


/**
 * Connect to the API and store all appointments if the connection is successful.
 * If the connection is not successful, show an error message on the LCD.
 */
void AppointmentManager::connectToAPI() {
    screen.printText("Connecting", "to API...");
    // Initialize a wi-fi client & http client
    WiFiClientSecure client;
    client.setFingerprint(FINGERPRINT);
    HTTPClient httpClient;

    // Set the URL of where the call should be made to.
    httpClient.begin(client, String(BASE_URL) + API_READ_APPOINTMENTS);

    // Make the GET-request, this returns the HTTP-code.
    int httpCode = httpClient.GET();

    // Initialize boolean to check if the connection was successful
    boolean connectionSuccessful = false;

    if (httpCode > 0) { // httpCode will be negative if it is an HttpClient error
        String payload = httpClient.getString();
        jsonBuffer.clear();
        deserializeJson(jsonBuffer, payload);
        String message = jsonBuffer["message"];

        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
        if (message != "null") {
            if (httpCode == HTTP_CODE_OK) {
                connectionSuccessful = true;
                Serial.println("Successfully connected to API");
                storeAllAppointments(payload);
            } else {
                Serial.println(message);
            }
        } else {
            Serial.printf("[HTTPS] GET... failed, error (%d)\n", httpCode);
        }
    } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", httpClient.errorToString(httpCode).c_str());
    }

    // Show the correct message on the LCD
    if (connectionSuccessful) {
        screen.printText(String(records.size()) + " " + getPluralizedAppointmentsString(), "found");
    } else {
        screen.printText("Error ${httpCode}", "Failed to connect");
    }

    delay(5000);
}

/**
 * Store all appointments in the records variable
 *
 * @param payload The JSON payload from the API
 */
void AppointmentManager::storeAllAppointments(String payload) {
    deserializeJson(jsonBuffer, payload);
    records = jsonBuffer["records"];
}

/**
 * Display how many appointments are found on the LCD
 */
void AppointmentManager::displayState() {
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
boolean AppointmentManager::displayNextAppointment(TimeManager timeManager) {
    if (records.size() == 0) return false;

    // If we are at the end of the list, reset the index to 0 and return false
    if (currentAppointmentIndex >= static_cast<int>(records.size())) {
        currentAppointmentIndex = 0;
        return false;
    }


    JsonObject appointment = records[currentAppointmentIndex];
    String name = appointment["name"];
    String time = timeManager.convertUTCtoLocalTime(appointment["start"]);

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
String AppointmentManager::getPluralizedAppointmentsString() {
    return records.size() == 1 ? "appointment" : "appointments";
}
