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
#include "InternetManager.h"
#include "TimeManager.h"
#include "Hygrometer.h"
#include "AppointmentManager.h"
#include "CuckooMechanism.h"


class StateManager {
public:
    StateManager(Screen screen, CuckooMechanism cuckooMechanism, TimeManager timeManager, Hygrometer hygrometer,
                 AppointmentManager appointments);

    void initialize(const Screen &givenScreen);

    void checkToGoBackToTimeDisplay();

    void checkToUpdateDisplay();

    void checkButtonPress();

    void checkToActivateCuckooMechanism();

private:
    Screen screen;
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
    const unsigned long timeToGoBackToTimeDisplay = 15 * 1000;
    const unsigned long timeToWaitForNextButtonPress = 500;

    static String getDisplayStateString(DisplayState displayState);

    int getCurrentUpdateInterval();

    void displayContent(bool updateDisplay);

    void changeCurrentDisplayState(DisplayState displayState);

    void goToNextDisplayState();
};


#endif //STATE_MANAGER_H
