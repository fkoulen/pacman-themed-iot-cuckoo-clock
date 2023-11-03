/*
 * Implementation of the StateManager class.
 * This class is used to control the display state and listen to the button presses.
 * It is also responsible for activating the cuckoo mechanism when needed.
 *
 * @author F.S. Koulen
 * @details License: GNU GPLv3
 * <br/>
 */

#include "StateManager.h"

/**
 * Initialize the state manager with the given components.
 */
StateManager::StateManager(Screen *screen, CuckooMechanism cuckooMechanism, TimeManager timeManager,
                           Hygrometer hygrometer, AppointmentManager appointments) : screen(screen), cuckooMechanism(
        std::move(cuckooMechanism)), timeManager(std::move(timeManager)), hygrometer(std::move(hygrometer)),
                                                                                     appointments(
                                                                                             std::move(appointments)) {
    httpsClient = new HTTPSClient();
}

/**
 * Set the givenScreen for the state manager and its components. Then change the display state to TIME.
 *
 * @param givenScreen The screen to display the content on for the state manager and its components
 */
void StateManager::initialize(Screen *givenScreen) {
    this->screen = givenScreen;
    timeManager.initialize(screen);
    hygrometer.initialize(screen, httpsClient);
    appointments.initialize(screen, httpsClient);
    appointments.fetch();
    cuckooMechanism.initialize(screen);
    changeCurrentDisplayState(TIME);
}

/**
 * Check if it's time to go back to the time display. If it is, change the display state to TIME.
 */
void StateManager::checkToGoBackToTimeDisplay() {
    // If the current display state is not TIME and the time since the last button press is greater than
    // the time to go back to the time display, change the display state to TIME.
    if (currentDisplayState != TIME && millis() - lastButtonPressTime >= TIME_TO_GO_BACK_TO_TIME_DISPLAY) {
        changeCurrentDisplayState(TIME);
    }
}

/**
 * Check if it's time to update the current display state. If it is, update the display.
 *
 * @param currentTime The current time in milliseconds
 */
void StateManager::checkToUpdateDisplay() {
    unsigned long currentTime = millis();

    // If the time since the last display update is greater than the update interval for the current display state,
    // update the display.
    if (currentTime - lastDisplayUpdateTime >= static_cast<unsigned long int>(getCurrentUpdateInterval())) {
        // Display the content and update the last display instead of clearing it
        displayContent(true);
        lastDisplayUpdateTime = currentTime;
    }
}

/**
 * Check if the button is pressed to switch display mode
 */
void StateManager::checkButtonPress() {
    // If the next button is pressed, switch to the next display state
    if (digitalRead(NEXT_BUTTON_PIN) == HIGH) {
        lastButtonPressTime = millis();
        // If the backlight is off, turn it on and display the time
        if (!screen->isBacklightOn()) {
            screen->toggleBacklight();
            displayTime();
        } else { // Otherwise, go to the next display state
            goToNextDisplayState();
        }

        delay(NEXT_BUTTON_DEBOUNCE_TIME);
    }

    // The play button is connected to an analog pin, so we need to use analogRead instead of digitalRead
    // to check if the button is pressed. The button is pressed when the analog value is close to 1024.
    // So we check if the analog value is greater than 1000.
    if (analogRead(PLAY_BUTTON_ANALOG_PIN) > MIN_HIGH_ANALOG_VALUE) {
        executeCuckooMechanism(timeManager.getDateTime());
        changeCurrentDisplayState(TIME);
    }
}

/**
 * Check if it's time to activate the cuckoo mechanism.
 * If it is, activate the cuckoo mechanism and change the display state to TIME afterward.
 */
void StateManager::checkToActivateCuckooMechanism() {
    RtcDateTime now = timeManager.getDateTime();
    unsigned long int currentHour = now.Hour();

    // It is time to activate the cuckoo mechanism if it has not been activated yet this hour
    if (lastCuckooMechanismActivationHour != currentHour) {
        executeCuckooMechanism(now);
        lastCuckooMechanismActivationHour = currentHour;
        changeCurrentDisplayState(TIME);
    }
}

/**
 * Change the display state to TIME and display the time.
 */
void StateManager::displayTime() {
    changeCurrentDisplayState(TIME);
}

/**
 * Execute the cuckoo mechanism and check if the backlight should be turned on during.
 */
void StateManager::executeCuckooMechanism(RtcDateTime currentTime) {
    bool backlightOffAtStart = !screen->isBacklightOn();
    if (backlightOffAtStart) screen->toggleBacklight();
    cuckooMechanism.executeCuckooMechanism(currentTime);
    if (backlightOffAtStart) screen->toggleBacklight();
}

/**
 * Get the display state as a string
 *
 * @param displayState The display state to get as a string
 * @return The display state as a string
 */
String StateManager::getDisplayStateString(DisplayState displayState) {
    switch (displayState) {
        case TIME:
            return "Time";
        case HYGROMETER:
            return "Hygrometer";
        case APPOINTMENTS:
            return "AppointmentManager";
        default:
            return "Time";
    }
}

/**
 * Display the content of the current display state
 *
 * @param update Whether to update the display instead of clearing it. By default, the display is cleared.
 */
void StateManager::displayContent(const bool update = false) {
    // If the screen should not be updated, clear it
    if (!update) screen->clear();

    // Display the content of the current display state, or the time if the current display state is invalid
    switch (currentDisplayState) {
        case TIME:
            /* If the screen should be updated, update the time. Otherwise, display the time.
            This is done to prevent the time from flickering when the screen is updated. */
            update ? timeManager.updateDateTime() : timeManager.displayTime();
            break;
        case HYGROMETER:
            hygrometer.displayState();
            break;
        case APPOINTMENTS:
            appointments.displayState();
            break;
        default:
            timeManager.displayTime();
    }
}

/**
 * Change the current display state
 *
 * @param displayState The display state to change to
 */
void StateManager::changeCurrentDisplayState(DisplayState displayState) {
    currentDisplayState = displayState;
    Serial.println("Switched to display mode: " + getDisplayStateString(currentDisplayState));
    displayContent();
}

/**
 * Go to the next display state
 */
void StateManager::goToNextDisplayState() {
    // If the current display state is appointments and there is an appointment to display,
    // don't switch to the next display state, but display the next appointment.
    if (currentDisplayState == APPOINTMENTS && appointments.displayNextAppointment(timeManager)) {
        return;
    }

    // Otherwise, switch to the next display state. If the current display state is the last one,
    // switch to the first one.
    auto nextDisplayState = static_cast<DisplayState>((currentDisplayState + 1) % NUMBER_OF_DISPLAYS);
    changeCurrentDisplayState(nextDisplayState);
}

/**
 * Get the update interval for the current display state
 *
 * @return The update interval in milliseconds
 */
int StateManager::getCurrentUpdateInterval() {
    switch (currentDisplayState) {
        case TIME:
            return timeManager.UPDATE_INTERVAL;
        case HYGROMETER:
            return hygrometer.UPDATE_INTERVAL;
        case APPOINTMENTS:
            return appointments.UPDATE_INTERVAL;
        default:
            return timeManager.UPDATE_INTERVAL;
    }
}

/**
 * Post a measurement to the API. Print the response to the serial monitor.
 * Show that the measurement is being posted on the LCD screen.
 *
 * @return The response code of the POST request
 */
int StateManager::postMeasurement() {
    screen->printText("Posting measure-", "ment to API...");
    int response = hygrometer.postMeasurement();
    screen->printText("Response code: ", String(response));
    delay(TIME_TO_SHOW_MESSAGE);
    displayTime();

    return response;
}