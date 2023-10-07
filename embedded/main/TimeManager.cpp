/**
 * Implementation of the TimeManager class. This class is used to display the time on the LCD screen.
 *
 * @author F.S. Koulen
 * @date 2023-10-02
 */

#include "TimeManager.h"


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
void TimeManager::initialize(Screen givenScreen) {
    givenScreen.printText("Initializing", "RTC module");

    setDebug(INFO); // Enable debug output from ezTime to serial
    waitForSync(); // Wait for NTP sync to complete

    timeZone.setLocation(TIME_ZONE);

    rtc.Begin();
    rtc.SetIsWriteProtected(false); // Unlock RTC for writing
    rtc.SetIsRunning(true); // Enable RTC

    rtc.SetDateTime(RtcDateTime(timeZone.year(), timeZone.month(), timeZone.day(), timeZone.hour(), timeZone.minute(),
                                timeZone.second())); // Set RTC time to NTP time

    rtc.SetIsWriteProtected(true); // Lock RTC for writing

    this->screen = std::move(givenScreen);
}

/**
 * Display the time on the screen.
 */
void TimeManager::displayTime() {
    RtcDateTime now = rtc.GetDateTime();

    if (!isValidDateTime(now)) {
        return;
    }

    DateTime dateTime = DateTime(now);

    screen.printText(datePrefix + dateTime.date, timePrefix + dateTime.time);
}

/**
 * Update the time on the screen instead of clearing the screen and redrawing the time.
 * This is used to prevent flickering. Should only be called if displayTime() has been called before.
 */
void TimeManager::updateDateTime() {
    RtcDateTime now = rtc.GetDateTime();

    if (!isValidDateTime(now)) {
        return;
    }

    DateTime dateTime = DateTime(now);

    screen.printText(dateTime.date, datePrefix.length(), dateTime.time, timePrefix.length(), false);
}

/**
 * Check if the given date and time are valid.
 *
 * @param dateTime The date and time to check
 */
bool TimeManager::isValidDateTime(const RtcDateTime &dateTime) {
    if (!dateTime.IsValid()) {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
        screen.printText("Could not", "retrieve time");
        return false;
    }

    return true;
}

/**
 * Get the current date and time.
 *
 * @return The current date and time
 */
RtcDateTime TimeManager::getDateTime() {
    return rtc.GetDateTime();
}


// ---------------------------------- DateTime ----------------------------------

/**
 * Constructor for the DateTime class.
 *
 * @param dateTime The date and time to use for this DateTime object.
 */
DateTime::DateTime(RtcDateTime dateTime) {
    char dateString[CHARACTERS_PER_LINE];
    char timeString[CHARACTERS_PER_LINE];

    sprintf(dateString, "%02u/%02u/%04u", dateTime.Day(), dateTime.Month(), dateTime.Year());

    sprintf(timeString, "%02d:%02d:%02d", dateTime.Hour(), dateTime.Minute(), dateTime.Second());

    this->date = String(dateString);
    this->time = String(timeString);
}