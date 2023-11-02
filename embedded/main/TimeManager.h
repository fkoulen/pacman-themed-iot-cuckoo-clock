/**
 * Represents the manager for displaying the time and date and converting UTC time to local time.
 *
 * @author F.S. Koulen
 * @details License: GNU GPLv3
 */

#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <Arduino.h>
#include <RtcDS1302.h>
#include <ezTime.h>
#include "Screen.h"

// See `TimeManager.cpp` for the implementation of the functions and their documentation.

class TimeManager {
public:
    explicit TimeManager(RtcDS1302<ThreeWire> rtc);

    void initialize(Screen *screen);

    void displayTime();

    void updateDateTime();

    RtcDateTime getDateTime();

    String convertUTCtoLocalTime(const String &utcTime);

    /**
     * The interval in milliseconds to update the time display.
     * This is set to 1000 milliseconds, so the time display is updated every second.
     */
    const int UPDATE_INTERVAL = 1000;

private:
    /**
     * Holds the current time zone.
     */
    Timezone timeZone;
    /**
     * Holds the RTC object to use for getting the time.
     */
    RtcDS1302<ThreeWire> rtc;
    /**
     * Holds the screen to use for displaying the time.
     */
    Screen *screen;
    /**
     * Holds the prefix for the date to display on the screen.
     */
    String datePrefix = "Date: ";
    /**
     * Holds the prefix for the time to display on the screen.
     */
    String timePrefix = "Time: ";

    static void configureTimeForCertificate();


    bool isValidDateTime(const RtcDateTime &dateTime);


    /**
     * Represents the date and time in a readable format.
     * This makes it easier to display the date and time on the screen.
     */
    class DateTime {
    public:
        explicit DateTime(RtcDateTime dateTime);

        /**
         * Holds the date.
         */
        String date;
        /**
         * Holds the time.
         */
        String time;
    };
};

#endif //TIME_MANAGER_H
