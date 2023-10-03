/*
 * A StateManager object is used to manage the state of the display and to handle button presses.
 *
 * @author F.S. Koulen
 * @date 2023-10-03
 */

#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <Arduino.h>
#include "../Screen/Screen.h"
#include "../WiFiManager/WiFiManager.h"
#include "../TimeManager/TimeManager.h"
#include "../Hygrometer/Hygrometer.h"
#include "../Appointments/Appointments.h"


class StateManager {
public:
    StateManager(Screen screen, TimeManager timeManager, Hygrometer hygrometer, Appointments appointments);

    void initialize(const Screen &givenScreen);

    void checkToGoBackToTimeDisplay();

    void checkToUpdateDisplay();

    void checkButtonPress();

private:
    Screen screen;
    TimeManager timeManager;
    Hygrometer hygrometer;
    Appointments appointments;
    enum DisplayState {
        TIME,
        HYGROMETER,
        APPOINTMENTS
    };
    const int NUMBER_OF_DISPLAYS = 3; // Update this when adding a new display state
    DisplayState currentDisplayState = TIME;
    unsigned long lastDisplayUpdateTime = 0;
    unsigned long lastButtonPressTime = 0;
    const unsigned long timeToGoBackToTimeDisplay = 15 * 1000;
    const unsigned long timeToWaitForNextButtonPress = 500;

    static String getDisplayStateString(DisplayState displayState);

    int getCurrentUpdateInterval();

    void displayContent(bool updateDisplay);

    void changeCurrentDisplayState(DisplayState displayState);
};


#endif //STATE_MANAGER_H
