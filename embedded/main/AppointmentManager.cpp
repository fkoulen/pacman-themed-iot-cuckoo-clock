/*
 *
 */

#include "AppointmentManager.h"

AppointmentManager::AppointmentManager() : jsonBuffer(DynamicJsonDocument(JSON_BUFFER_SIZE)) {
}

void AppointmentManager::setScreen(Screen *givenScreen) {
    this->screen = givenScreen;
}


/**
 * Connect to the API and store all appointments if the connection is successful.
 * If the connection is not successful, show an error message on the LCD.
 */
void AppointmentManager::fetch() {
    screen->printText("Fetching", "appointments...");
    // Initialize a wi-fi client & http client
    WiFiClientSecure client;
    char fingerprint[] = FINGERPRINT
    client.setFingerprint(fingerprint);
    HTTPClient httpClient;

    // Set the URL of where the call should be made to.
    httpClient.begin(client, String(BASE_URL) + API_READ_APPOINTMENTS);

    // Custom header to tell the tunnel that we don't want to see the screen
    httpClient.addHeader("X-Pinggy-No-Screen", "true");
    httpClient.addHeader("Bypass-Tunnel-Reminder", "false");

    // Make the GET-request, this returns the HTTP-code.
    int httpCode = httpClient.GET();

    // Initialize boolean to check if the connection was successful
    boolean connectionSuccessful = false;

    if (HTTPClient::errorToString(httpCode) == String()) { // Check if it is not an HTTPClient error
        String payload = httpClient.getString();
        jsonBuffer.clear();
        deserializeJson(jsonBuffer, payload);
        String message = jsonBuffer["message"];

        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK) {
            connectionSuccessful = true;
            Serial.println("Successfully connected to API");
            storeAllAppointments(payload);
        } else if (message != "null") {
            Serial.println(message);
        } else {
            Serial.printf("[HTTPS] GET... failed, error (%d)\n", httpCode);
        }
    } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", HTTPClient::errorToString(httpCode).c_str());
    }

    // Show the correct message on the LCD
    if (connectionSuccessful) {
        screen->printText(String(records.size()) + " " + getPluralizedAppointmentsString(), "found");
    } else {
        screen->printText("Error " + String(httpCode), "Failed to connect");
    }

    delay(TIME_TO_SHOW_MESSAGE);
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
        screen->printText("No appointments", "found");
        return;
    }

    screen->printText("Next 7 days:", String(records.size()) + " " + getPluralizedAppointmentsString());
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

    screen->printText(appointmentNumber + ": " + name, time);

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
