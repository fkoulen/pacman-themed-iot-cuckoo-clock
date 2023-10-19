// #include "Constants.h"
// #include "StateManager.h"
// #include "Screen.h"
// #include "InternetManager.h"
// #include "TimeManager.h"
// #include "Hygrometer.h"
// #include "AppointmentManager.h"
// #include "CuckooMechanism.h"
//
// Screen *screen = new Screen();
// ThreeWire rtcWiring(RTC_DAT_PIN, RTC_CLK_PIN, RTC_RST_PIN);
// TimeManager timeManager = TimeManager(rtcWiring);
// DHT dht(DHT_PIN, DHT_TYPE);
// Hygrometer hygrometer = Hygrometer(dht);
// AppointmentManager appointments = AppointmentManager();
// CuckooMechanism cuckooMechanism = CuckooMechanism();
// StateManager *stateManager = new StateManager(screen, cuckooMechanism, timeManager, hygrometer, appointments);
// InternetManager *internetManager = new InternetManager();
//
// void setup() {
//     pinMode(NEXT_BUTTON_PIN, INPUT);
//     Serial.begin(SERIAL_BAUD_RATE);
//     Serial.println(); // Print empty line to separate boot messages from the rest of the output
//     screen->initializeLCD();
//     internetManager->initialize(screen, stateManager);
//     stateManager->initialize(screen);
// }
//
// void loop() {
//     internetManager->listenServer();
//     stateManager->checkToActivateCuckooMechanism();
//     stateManager->checkToGoBackToTimeDisplay();
//     stateManager->checkToUpdateDisplay();
//     stateManager->checkButtonPress();
// }