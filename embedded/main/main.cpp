#include <Arduino.h>
#include "Constants.h"
#include "StateManager/StateManager.h"
#include "Screen/Screen.h"
#include "WiFiManager/WiFiManager.h"
#include "TimeManager/TimeManager.h"
#include "Hygrometer/Hygrometer.h"
#include "Appointments/Appointments.h"
#include "CuckooMechanism/CuckooMechanism.h"

Screen screen = Screen();
WiFiManager wifiManager;
ThreeWire rtcWiring(RTC_DAT_PIN, RTC_CLK_PIN, RTC_RST_PIN);
TimeManager timeManager = TimeManager(rtcWiring);
DHT dht(DHT_PIN, DHT_TYPE);
Hygrometer hygrometer = Hygrometer(dht);
Appointments appointments = Appointments();
CuckooMechanism cuckooMechanism = CuckooMechanism();
StateManager stateManager = StateManager(screen, cuckooMechanism, timeManager, hygrometer, appointments);

void setup() {
    pinMode(NEXT_BUTTON_PIN, INPUT_PULLUP);
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println(); // Print empty line to separate boot messages from the rest of the output
    screen.initializeLCD();
    wifiManager.initialize(screen, WIFI_SSID, WIFI_PASSWORD);
    stateManager.initialize(screen);
}

void loop() {
    stateManager.checkToGoBackToTimeDisplay();
    stateManager.checkToUpdateDisplay();
    stateManager.checkButtonPress();
}

