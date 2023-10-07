/**
 * A TimeManager object is used to display the time on the screen.
 *
 * @author F.S. Koulen
 * @date 2023-10-02
 */

#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <Arduino.h>
#include <RtcDS1302.h>
#include <ezTime.h>
#include "Screen.h"

class TimeManager {
public:
    explicit TimeManager(RtcDS1302<ThreeWire> rtc);

    void initialize(Screen screen);

    void displayTime();

    void updateDateTime();

    int updateInterval = 1000;

    RtcDateTime getDateTime();
private:
    Timezone timeZone;
    RtcDS1302<ThreeWire> rtc;
    Screen screen;
    String datePrefix = "Date: ";
    String timePrefix = "Time: ";


    bool isValidDateTime(const RtcDateTime &dateTime);
};

class DateTime {
public:
    explicit DateTime(RtcDateTime dateTime);
    String date;
    String time;
};

#endif //TIME_MANAGER_H
