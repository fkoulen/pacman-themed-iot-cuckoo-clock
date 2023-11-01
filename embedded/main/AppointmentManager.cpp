/**
 * Implementation of the AppointmentManager class. It has methods to fetch, store and display appointments.
 *
 * @author F.S. Koulen
 * @license GNU GPLv3
 */

#include "AppointmentManager.h"

/**
 * Constructor of the AppointmentManager class.
 * It initializes the JSON buffer with the correct size.
 */
AppointmentManager::AppointmentManager() : jsonBuffer(DynamicJsonDocument(JSON_BUFFER_SIZE)) {
}

/**
 * Set the screen to use for displaying the appointments.
 *
 * @param givenScreen The screen to use for displaying the appointments
 */
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

    // If the HTTP code is an HTTPClient error code, print the error
    if (!(HTTPClient::errorToString(httpCode) ==
          String())) {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", HTTPClient::errorToString(httpCode).c_str());
    } else { // If not, it has a valid HTTP code
        String payload = httpClient.getString();
        jsonBuffer.clear();
        deserializeJson(jsonBuffer, payload);
        String message = jsonBuffer["message"];

        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

        // If the HTTP code is 200, the connection was successful and the appointments can be stored
        if (httpCode == HTTP_CODE_OK) {
            connectionSuccessful = true;
            Serial.println("Successfully connected to API");
            storeAllAppointments(payload);
        } else if (message != "null") { // If the error message is not null, print the message
            Serial.println(message);
        } else { // If the error message is null, print the HTTP code
            Serial.printf("[HTTPS] GET... failed, error (%d)\n", httpCode);
        }
    }

    // If the connection was successful, show the number of appointments on the LCD
    if (connectionSuccessful) {
        screen->printText(String(records.size()) + " " + getPluralizedAppointmentsString(), "found");
    } else { // If the connection was not successful, show an error message on the LCD
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
    if (records.size() == 0) { // If there are no appointments, show a message on the LCD
        Serial.println("No appointments found");
        screen->printText("No appointments", "found");
        return;
    }

    // Else, show the number of appointments on the LCD
    screen->printText("Next 7 days:", String(records.size()) + " " + getPluralizedAppointmentsString());
}

/**
 * Display the next appointment on the LCD. If there is no next appointment to display, return false.
 *
 * @param timeManager The TimeManager to use for converting the UTC time to local time
 * @return True if there is a next appointment to display, false otherwise
 */
boolean AppointmentManager::displayNextAppointment(TimeManager timeManager) {
    // If there are no appointments, return false
    if (records.size() == 0) return false;

    // If we are at the end of the list, reset the index to 0 and return false
    if (currentAppointmentIndex >= static_cast<int>(records.size())) {
        currentAppointmentIndex = 0;
        return false;
    }

    // Get the appointment name and time
    JsonObject appointment = records[currentAppointmentIndex];
    String name = appointment["name"];
    String time = timeManager.convertUTCtoLocalTime(appointment["start"]);

    String appointmentNumber = String(currentAppointmentIndex + 1); // Add 1 to the index since it starts at 0
    Serial.print("Displaying appointment " + appointmentNumber + ": ");
    Serial.println(name + " at " + time);

    screen->printText(appointmentNumber + ": " + name, time);

    currentAppointmentIndex++; // Increment the index so the next appointment will be displayed next time

    return true;
}

/**
 * Get the pluralized string of the word appointment
 *
 * @return Either "appointment" or "appointments" depending on the number of appointments
 */
String AppointmentManager::getPluralizedAppointmentsString() {
    return records.size() == 1 ? "appointment" : "appointments";
}
