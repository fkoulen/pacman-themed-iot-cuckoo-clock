//
// Created by feryl on 02/10/2023.
//

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
