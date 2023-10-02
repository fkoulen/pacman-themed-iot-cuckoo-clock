/**
 * Create a TimeManager object to display the time on the screen
 *
 * @author F.S. Koulen
 * @date 2023-10-02
 */

#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <Arduino.h>
#include "../Screen/Screen.h"
#include <RtcDS1302.h>

class TimeManager {
public:
    TimeManager(RtcDS1302<ThreeWire> rtc);
    void setScreen(Screen screen);
    void displayTime();
private:
    RtcDS1302<ThreeWire> rtc;
    Screen screen;
    int LCD_UPDATE_INTERVAL = 1000;
};


#endif //TIME_MANAGER_H
