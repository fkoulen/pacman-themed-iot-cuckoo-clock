/*
 *
 */

#include "StateManager.h"

/**
 * Initialize the state manager
 */
StateManager::StateManager(Screen screen, TimeManager timeManager, Hygrometer hygrometer)
        : screen(std::move(screen)), timeManager(std::move(timeManager)), hygrometer(std::move(hygrometer)) {
}

/**
 * Set the screen for the state manager
 *
 * @param screen The screen
 */
void StateManager::setScreen(const Screen& givenScreen) {
    this->screen = givenScreen;
    timeManager.setScreen(givenScreen);
    hygrometer.setScreen(givenScreen);
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
        default:
            return timeManager.updateInterval;
    }
}

/**
 * Display the content of the current display state
 */
void StateManager::displayContent() {
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

    if (currentTime - lastDisplayUpdateTime >= getCurrentUpdateInterval()) {
        displayContent();
        lastDisplayUpdateTime = currentTime;
    }
}

/**
 * Check if the button is pressed to switch display mode
 */
void StateManager::checkButtonPress() {
    if (digitalRead(NEXT_BUTTON_PIN) == HIGH) {
        lastButtonPressTime = millis();
        auto nextDisplayState = static_cast<DisplayState>((currentDisplayState + 1) % NUMBER_OF_DISPLAYS);
        changeCurrentDisplayState(nextDisplayState);
        delay(1000); // Debounce the button press
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
