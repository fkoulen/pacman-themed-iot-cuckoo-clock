/**
 * Implementation of the TimeManager class. This class is used to display the time on the LCD screen.
 *
 * @author F.S. Koulen
 * @date 2023-10-02
 */

#include "TimeManager.h"
#include <RtcDS1302.h>

#include <utility>

/**
 * Constructor for the TimeManager class.
 *
 * @param rtc The RTC object to use for getting the time.
 */
TimeManager::TimeManager(RtcDS1302<ThreeWire> rtc) : rtc(rtc) {
}

/**
 * Set the screen to use for displaying the time.
 */
void TimeManager::setScreen(Screen givenScreen) {
    this->screen = std::move(givenScreen);
}

/**
 * Display the time on the screen.
 */
void TimeManager::displayTime() {
    RtcDateTime now = rtc.GetDateTime();

    if (!now.IsValid()) {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
    }

    char dateString[CHARACTERS_PER_LINE];
    char timeString[CHARACTERS_PER_LINE];

    sprintf(dateString, "Date: %02u/%02u/%04u", now.Day(), now.Month(), now.Year());

    sprintf(timeString, "Time: %02d:%02d:%02d", now.Hour(), now.Minute(), now.Second());

    screen.printText(dateString, timeString);
}

