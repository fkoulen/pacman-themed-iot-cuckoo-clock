///**
// * Main file for the embedded system.
// * This file is responsible for initializing all the components and running the main loop.
// * The main loop checks for button presses, listens to incoming requests and updates the display.
// *
// * @author F.S. Koulen
// * @details License: GNU GPLv3
// */
//
//#include <Arduino.h>
//#include "Constants.h"
//#include "StateManager.h"
//#include "Screen.h"
//#include "InternetManager.h"
//#include "TimeManager.h"
//#include "Hygrometer.h"
//#include "AppointmentManager.h"
//#include "CuckooMechanism.h"
//
//// Initialize all the components
//Screen *screen = new Screen();
//ThreeWire rtcWiring(RTC_DAT_PIN, RTC_CLK_PIN, RTC_RST_PIN);
//TimeManager timeManager = TimeManager(rtcWiring);
//DHT dht(DHT_PIN, DHT_TYPE);
//Hygrometer hygrometer = Hygrometer(dht);
//AppointmentManager appointments = AppointmentManager();
//CuckooMechanism cuckooMechanism = CuckooMechanism();
//StateManager *stateManager = new StateManager(screen, cuckooMechanism, timeManager, hygrometer, appointments);
//InternetManager *internetManager = new InternetManager();
//
///**
// * Initialize the components and set up the serial connection.
// */
//void setup() {
//    pinMode(NEXT_BUTTON_PIN, INPUT);
//    Serial.begin(SERIAL_BAUD_RATE);
//    Serial.println(); // Print empty line to separate boot messages from the rest of the output
//    screen->initializeLCD();
//    internetManager->initialize(screen, stateManager);
//    stateManager->initialize(screen);
//}
//
///**
// * Listen for requests to the server, check for button presses, if the cuckoo mechanism should be activated,
// * if the display should be updated and if the time display should be shown.
// */
//void loop() {
//    internetManager->listenServer();
//    stateManager->checkToActivateCuckooMechanism();
//    stateManager->checkToGoBackToTimeDisplay();
//    stateManager->checkToUpdateDisplay();
//    stateManager->checkButtonPress();
//}