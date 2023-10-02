#include <Arduino.h>
#include "Constants.h"
#include "Screen/Screen.h"
#include "WiFiManager/WiFiManager.h"
#include "TimeManager/TimeManager.h"
#include "Hygrometer/Hygrometer.h"

Screen screen = Screen();
WiFiManager wifiManager;
ThreeWire rtcWiring(RTC_DAT_PIN, RTC_CLK_PIN, RTC_RST_PIN);
TimeManager timeManager = TimeManager(rtcWiring);
DHT dht(DHT_PIN, DHT_TYPE);
Hygrometer hygrometer = Hygrometer(dht);

enum DisplayState {
    TIME,
    HYGROMETER
};

const int NUMBER_OF_DISPLAYS = sizeof(DisplayState) / sizeof(int) + 1;

DisplayState currentDisplayState = TIME;
unsigned long lastDisplayUpdateTime = 0;

/*
 * Initialize the screen and set the screen for the other components
 */
void initializeScreen() {
    screen.initializeLCD();
    wifiManager.setScreen(screen);
    timeManager.setScreen(screen);
    hygrometer.setScreen(screen);
}

void setup() {
    pinMode(NEXT_BUTTON_PIN, INPUT_PULLUP);
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println(); // Print empty line to separate boot messages from the rest of the output
    initializeScreen();
    wifiManager.initializeWiFi(WIFI_SSID, WIFI_PASSWORD);
}

/**
 * Get the update interval for the current display state
 *
 * @return The update interval in milliseconds
 */
int getCurrentUpdateInterval() {
    switch (currentDisplayState) {
        case TIME:
            return timeManager.updateInterval;
        case HYGROMETER:
            return hygrometer.updateInterval;
        default:
            return timeManager.updateInterval;
    }
}

/**
 * Display the content of the current display state
 */
void displayContent() {
    screen.clear();
    switch (currentDisplayState) {
        case TIME:
            timeManager.displayTime();
            break;
        case HYGROMETER:
            hygrometer.displayState();
            break;
        default:
            timeManager.displayTime();
    }
}

/**
 * Switch the display state to the next one
 */
void switchDisplayState() {
    // Increment the display mode (cycle through the available modes)
    currentDisplayState = static_cast<DisplayState>((currentDisplayState + 1) % NUMBER_OF_DISPLAYS);

    String currentDisplayStateString;

    switch (currentDisplayState) {
        case TIME:
            currentDisplayStateString = "Time";
            break;
        case HYGROMETER:
            currentDisplayStateString = "Hygrometer";
            break;
        default:
            currentDisplayStateString = "Time";
    }

    Serial.println("Switched to display mode: " + currentDisplayStateString);
}

void loop() {
    unsigned long currentTime = millis();
    // Change getCurrentUpdateInterval to long
    unsigned long updateInterval = getCurrentUpdateInterval();

    // Check if it's time to update the display
    if (currentTime - lastDisplayUpdateTime >= updateInterval) {
        displayContent();
        lastDisplayUpdateTime = currentTime;
    }

    // Check if the button is pressed to switch display mode
    if (digitalRead(NEXT_BUTTON_PIN) == HIGH) {
        switchDisplayState();
        displayContent();
        delay(1000); // Debounce the button press
    }
}

