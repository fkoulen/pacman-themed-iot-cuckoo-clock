/*
 * A StateManager object is used to manage the state of the display and to handle button presses.
 *
 * @author F.S. Koulen
 * @date 2023-10-03
 */

#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <Arduino.h>
#include "Screen.h"
#include "TimeManager.h"
#include "Hygrometer.h"
#include "AppointmentManager.h"
#include "CuckooMechanism.h"


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
    Screen *screen;
    CuckooMechanism cuckooMechanism;
    TimeManager timeManager;
    Hygrometer hygrometer;
    AppointmentManager appointments;

    enum DisplayState {
        TIME,
        HYGROMETER,
        APPOINTMENTS
    };

    const int NUMBER_OF_DISPLAYS = 3; // Update this when adding a new display state
    DisplayState currentDisplayState = TIME;
    unsigned long lastDisplayUpdateTime = 0;
    unsigned long lastButtonPressTime = 0;
    unsigned long lastCuckooMechanismActivationHour = 0;
    const unsigned long TIME_TO_GO_BACK_TO_TIME_DISPLAY = 15 * 1000;
    const unsigned long NEXT_BUTTON_DEBOUNCE_TIME = 500;
    const unsigned long MIN_HIGH_ANALOG_VALUE = 1000;

    static String getDisplayStateString(DisplayState displayState);

    int getCurrentUpdateInterval();

    void displayContent(bool updateDisplay);

    void changeCurrentDisplayState(DisplayState displayState);

    void goToNextDisplayState();

    void executeCuckooMechanism(RtcDateTime currentTime);
};


#endif //STATE_MANAGER_H
