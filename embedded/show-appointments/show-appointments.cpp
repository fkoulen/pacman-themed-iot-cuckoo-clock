#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define WIFI_SSID      "iotroam"
#define WIFI_PASSWORD  "OQqcD8LpM7"
#define API_URL "http://koulenf.loca.lt/api/appointment/read.php"
#define JSON_BUFFER_SIZE 1024
#define NEXT_BUTTON 14

DynamicJsonDocument jsonBuffer(JSON_BUFFER_SIZE);

JsonArray records; // Used to store all the appointments
int currentAppointment = 0; // Index of the currently displayed appointment

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for 16 chars and 2 line display

/**
 * Initialize the LCD
 */
void initializeLCD() {
    lcd.init();         // Initialize the LCD
    lcd.backlight();    // Turn on the backlight
}

/**
 * Clear the LCD and show the given text on the first and second line
 *
 * @param firstLine The text for the first line
 * @param secondLine The text for the second line
 */
void showText(String firstLine, String secondLine) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(firstLine);
    lcd.setCursor(0, 1);
    lcd.print(secondLine);
}

/**
 * Initialize the Wi-Fi connection
 */
void initializeWifi() {
    showText("Connecting", "to Wi-Fi...");
    // Initialize the Serial-connection on a speed of 115200 b/s
    Serial.begin(115200);

    // Your WeMos tries to connect to your Wi-fi network
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // Keep the while-statement alive as long as we are NOT connected
    // to the Wi-fi network.
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }
}

/**
 * Store all appointments in the records variable
 *
 * @param payload The JSON payload from the API
 */
void storeAllAppointments(String payload) {
    deserializeJson(jsonBuffer, payload);
    records = jsonBuffer["records"];
}

/**
 * Connect to the API and store all appointments if the connection is successful.
 * If the connection is not successful, show an error message on the LCD.
 */
void connectToAPI() {
    showText("Connecting", "to API...");
    // Initialize a wi-fi client & http client
    WiFiClient client;
    HTTPClient httpClient;

    // Set the URL of where the call should be made to.
    httpClient.begin(client, API_URL);

    // Make the GET-request, this returns the HTTP-code.
    int httpCode = httpClient.GET();

    // Check if the response is fine.
    if (httpCode == HTTP_CODE_OK) { // HTTP_CODE_OK == 200
        String payload = httpClient.getString();
        storeAllAppointments(payload);
    } else if (httpCode == HTTP_CODE_NOT_FOUND) {
        showText("No appointments", "found");
    } else {
        String payload = httpClient.getString();
        deserializeJson(jsonBuffer, payload);
        String message = jsonBuffer["message"];
        showText("Error ${httpCode}", message);
    }
}

/**
 * Set the prefix for the given row on the LCD
 *
 * @param prefix prefix to set
 * @param row row to set the prefix on
 */
void setPrefix(String prefix, int row) {
    lcd.setCursor(0, row);
    lcd.print(prefix);
}

/**
 * Print the given appointment on the LCD
 *
 * @param record The appointment to print
 */
void printAppointment(JsonObject record) {
    // Get name
    String name = record["name"];
    // Get time
    String time = record["start"];

    lcd.clear();

    setPrefix("Name: ", 0);
    lcd.print(name); // Display the received name
    setPrefix("Time: ", 1);
    lcd.print(time); // Display the received time
}

void setup() {
    pinMode(NEXT_BUTTON, INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);
    initializeLCD();
    initializeWifi();
    connectToAPI();
    printAppointment(records[currentAppointment]); // Print the first appointment
}

void loop() {
    // On button press, show the next appointment
    if (digitalRead(NEXT_BUTTON) == HIGH) {
        currentAppointment++;
        // If we are at the end of the appointments, go back to the first one
        if (currentAppointment >= records.size()) {
            currentAppointment = 0;
        }
        printAppointment(records[currentAppointment]);
        delay(250); // Wait 250ms to prevent multiple button presses
    }
}