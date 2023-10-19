/*
 * Implementation of the StateManager class.
 * This class is used to control the display state and listen to the button presses.
 *
 * @author F.S. Koulen
 * @date 2023-10-03
 */

#include "StateManager.h"

#include <utility>

/**
 * Initialize the state manager
 */
StateManager::StateManager(
        Screen *screen,
        CuckooMechanism cuckooMechanism,
        TimeManager timeManager,
        Hygrometer hygrometer,
        AppointmentManager appointments)
        :
        screen(screen),
        cuckooMechanism(std::move(cuckooMechanism)),
        timeManager(std::move(timeManager)),
        hygrometer(std::move(hygrometer)),
        appointments(std::move(appointments)) {
}

/**
 * Set the givenScreen for the state manager and its components. Then change the display state to TIME.
 *
 * @param givenScreen The givenScreen
 */
void StateManager::initialize(Screen *givenScreen) {
    this->screen = givenScreen;
    timeManager.initialize(screen);
    hygrometer.setScreen(screen);
    appointments.setScreen(screen);
    appointments.connectToAPI();
    cuckooMechanism.initialize(screen);
    changeCurrentDisplayState(TIME);
}

/**
 * Get the display state as a string
 *
 * @param displayState The display state
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
 * Get the update interval for the current display state
 *
 * @return The update interval in milliseconds
 */
int StateManager::getCurrentUpdateInterval() {
    switch (currentDisplayState) {
        case TIME:
            return timeManager.updateInterval;
        case HYGROMETER:
            return hygrometer.updateInterval;
        case APPOINTMENTS:
            return appointments.updateInterval;
        default:
            return timeManager.updateInterval;
    }
}

/**
 * Display the content of the current display state
 *
 * @param update Whether to update the display instead of clearing it
 */
void StateManager::displayContent(const bool update = false) {
    if (!update) screen->clear();

    switch (currentDisplayState) {
        case TIME:
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
 * Check if it's time to go back to the time display
 *
 * @param currentTime The current time in milliseconds
 */
void StateManager::checkToGoBackToTimeDisplay() {
    if (currentDisplayState != TIME && millis() - lastButtonPressTime >= timeToGoBackToTimeDisplay) {
        changeCurrentDisplayState(TIME);
    }
}

/**
 * Check if it's time to switch the display state
 *
 * @param currentTime The current time in milliseconds
 */
void StateManager::checkToUpdateDisplay() {
    unsigned long currentTime = millis();

    if (currentTime - lastDisplayUpdateTime >= static_cast<unsigned long int>(getCurrentUpdateInterval())) {
        displayContent(true);
        lastDisplayUpdateTime = currentTime;
    }
}

/**
 * Check if the button is pressed to switch display mode
 */
void StateManager::checkButtonPress() {
    if (digitalRead(NEXT_BUTTON_PIN) == HIGH) {
        lastButtonPressTime = millis();
        if (!screen->isBacklightOn()) {
            screen->toggleBacklight();
            displayContent();
        } else {
            goToNextDisplayState();
            delay(timeToWaitForNextButtonPress);
        }
    }

    // The play button is connected to an analog pin, so we need to use analogRead instead of digitalRead
    // to check if the button is pressed. The button is pressed when the analog value is close to 1024.
    // So we check if the analog value is greater than 1000.
    if (analogRead(PLAY_BUTTON_ANALOG_PIN) > 1000) {
        cuckooMechanism.executeCuckooMechanism(timeManager.getDateTime());
        changeCurrentDisplayState(TIME);
    }
}

/**
 * Change the current display state
 *
 * @param displayState The new display state
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

    auto nextDisplayState = static_cast<DisplayState>((currentDisplayState + 1) % NUMBER_OF_DISPLAYS);
    changeCurrentDisplayState(nextDisplayState);
}

/**
 * Check if it's time to activate the cuckoo mechanism.
 * If it is, activate the cuckoo mechanism and change the display state to TIME afterwards.
 *
 * @param now The current time
 */
void StateManager::checkToActivateCuckooMechanism() {
    RtcDateTime now = timeManager.getDateTime();
    unsigned long int currentHour = now.Hour();

    // It is time to activate the cuckoo mechanism if it has not been activated yet this hour
    if (lastCuckooMechanismActivationHour != currentHour) {
        if (!screen->isBacklightOn()) {
            screen->toggleBacklight();
        }
        cuckooMechanism.executeCuckooMechanism(now);
        lastCuckooMechanismActivationHour = currentHour;
        changeCurrentDisplayState(TIME);
    }
}

/**
 * Display the time on the LCD
 */
void StateManager::displayTime() {
    changeCurrentDisplayState(TIME);
}