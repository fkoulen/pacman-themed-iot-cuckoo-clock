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


class StateManager {
public:
    StateManager(Screen screen, TimeManager timeManager, Hygrometer hygrometer);

    void initialize(const Screen &screen);

    void checkToGoBackToTimeDisplay();

    void checkToUpdateDisplay();

    void checkButtonPress();

private:
    Screen screen;
    TimeManager timeManager;
    Hygrometer hygrometer;
    enum DisplayState {
        TIME,
        HYGROMETER
    };
    DisplayState currentDisplayState = TIME;
    const int NUMBER_OF_DISPLAYS = sizeof(DisplayState) / sizeof(int) + 1;
    unsigned long lastDisplayUpdateTime = 0;
    unsigned long lastButtonPressTime = 0;
    unsigned long timeToGoBackToTimeDisplay = 15 * 1000;

    static String getDisplayStateString(DisplayState displayState);

    int getCurrentUpdateInterval();

    void displayContent(const bool updateDisplay);

    void changeCurrentDisplayState(DisplayState displayState);
};


#endif //STATE_MANAGER_H
