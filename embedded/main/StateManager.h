/**
 * Represents the manager for the state of the embedded system.
 * This class is responsible for changing the display state,
 * checking for button presses and activating the cuckoo mechanism when needed.
 *
 * @author F.S. Koulen
 * @details License: GNU GPLv3
 */

#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <Arduino.h>
#include "Screen.h"
#include "TimeManager.h"
#include "Hygrometer.h"
#include "AppointmentManager.h"
#include "CuckooMechanism.h"

// See `StateManager.cpp` for the implementation of the functions and their documentation.

class StateManager {
public:
    StateManager(Screen *screen,
                 CuckooMechanism cuckooMechanism,
                 TimeManager timeManager,
                 Hygrometer hygrometer,
                 AppointmentManager appointments);

    void initialize(Screen *givenScreen);

    void checkToGoBackToTimeDisplay();

    void checkToUpdateDisplay();

    void checkButtonPress();

    void checkToActivateCuckooMechanism();

    void displayTime();

    int postMeasurement();

private:
    /**
     * The screen to display the content on
     */
    Screen *screen;
    /**
     * The cuckoo mechanism to activate when needed
     */
    CuckooMechanism cuckooMechanism;
    /**
     * The time manager to change the display state to when needed
     */
    TimeManager timeManager;
    /**
     * The hygrometer to change the display state to when needed
     */
    Hygrometer hygrometer;
    /**
     * The appointment manager to change the display state to when needed
     */
    AppointmentManager appointments;

    /**
     * The display states
     * TIME: Display the time
     * HYGROMETER: Display the humidity and temperature
     * APPOINTMENTS: Display the appointments
     */
    enum DisplayState {
        TIME,
        HYGROMETER,
        APPOINTMENTS
    };

    /**
     * Number of display states.
     * Update this when adding a new display state to the enum above.
     */
    const int NUMBER_OF_DISPLAYS = 3;
    /**
     * The current display state.
     * Default is TIME.
     */
    DisplayState currentDisplayState = TIME;
    /**
     * The last time the display was updated.
     * Default is 0.
     */
    unsigned long lastDisplayUpdateTime = 0;
    /**
     * The last time the button was pressed.
     * Default is 0.
     */
    unsigned long lastButtonPressTime = 0;
    /**
     * The last time the cuckoo mechanism was activated.
     * Default is 0.
     */
    unsigned long lastCuckooMechanismActivationHour = 0;
    /**
     * The time in milliseconds to go back to the time display after changing the display state.
     */
    const unsigned long TIME_TO_GO_BACK_TO_TIME_DISPLAY = 15 * 1000;
    /**
     * The time in milliseconds to wait before listening to the button again.
     */
    const unsigned long NEXT_BUTTON_DEBOUNCE_TIME = 500;
    /**
     * The minimum value of the analog pin to activate the cuckoo mechanism.
     */
    const unsigned long MIN_HIGH_ANALOG_VALUE = 1000;

    static String getDisplayStateString(DisplayState displayState);

    int getCurrentUpdateInterval();

    void displayContent(bool updateDisplay);

    void changeCurrentDisplayState(DisplayState displayState);

    void goToNextDisplayState();

    void executeCuckooMechanism(RtcDateTime currentTime);
};


#endif //STATE_MANAGER_H
