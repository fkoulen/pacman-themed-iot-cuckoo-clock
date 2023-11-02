/**
 * Implementation of the TimeManager class.
 * This class is used to display the time on the LCD screen and to convert UTC time to local time.
 *
 * @author F.S. Koulen
 * @details License: GNU GPLv3
 * <br/>
 */

#include "TimeManager.h"


/**
 * Constructor for the TimeManager class.
 * Creates a TimeManager object and initializes the RTC object to use for getting the current date and time.
 *
 * @param rtc The RTC object to use for getting the current date and time
 */
TimeManager::TimeManager(RtcDS1302<ThreeWire> rtc) : rtc(rtc) {
}

/**
 * Initialize the TimeManager object by setting the screen to use for displaying the time and initializing the RTC.
 * This method also waits for the NTP sync to complete and sets the RTC time to the NTP time.
 * The NTP time is converted to the local time zone before setting the RTC time.
 * The RTC is then locked for writing.
 *
 * @param givenScreen The screen to use for displaying the time
 */
void TimeManager::initialize(Screen *givenScreen) {
    this->screen = givenScreen;
    screen->printText("Initializing", "RTC module");

    setDebug(INFO); // Enable debug output from ezTime to serial
    waitForSync(); // Wait for NTP sync to complete

    timeZone.setLocation(TIME_ZONE);

    rtc.Begin();
    rtc.SetIsWriteProtected(false); // Unlock RTC for writing
    rtc.SetIsRunning(true); // Enable RTC

    rtc.SetDateTime(RtcDateTime(timeZone.year(), timeZone.month(), timeZone.day(), timeZone.hour(), timeZone.minute(),
                                timeZone.second())); // Set RTC time to NTP time

    rtc.SetIsWriteProtected(true); // Lock RTC for writing
}

/**
 * Display the current date and time on the screen.
 */
void TimeManager::displayTime() {
    RtcDateTime now = getDateTime();

    if (!isValidDateTime(now)) {
        return;
    }

    DateTime dateTime = DateTime(now);

    screen->printText(datePrefix + dateTime.date, timePrefix + dateTime.time);
}

/**
 * Update the time on the screen instead of clearing the screen and redrawing the time.
 * This is used to prevent flickering. Should only be called if displayTime() has been called before.
 *
 * @see displayTime()
 */
void TimeManager::updateDateTime() {
    RtcDateTime now = getDateTime();

    if (!isValidDateTime(now)) {
        return;
    }

    DateTime dateTime = DateTime(now);

    screen->printText(dateTime.date, datePrefix.length(), dateTime.time, timePrefix.length(), false);
}

/**
 * Check if the given date and time are valid.
 *
 * @param dateTime The date and time to check
 * @return True if the date and time are valid, false otherwise
 */
bool TimeManager::isValidDateTime(const RtcDateTime &dateTime) {
    if (!dateTime.IsValid()) {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
        screen->printText("Could not", "retrieve time");
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

/**
 * Convert the given UTC time to local time.
 *
 * @param utcTime The UTC time to convert
 * @return The local time
 */
String TimeManager::convertUTCtoLocalTime(const String &utcTime) {
    auto utcString = utcTime.c_str();

    int year, month, day, hour, minute, second;
    sscanf(utcString, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
    const time_t time = makeTime(hour, minute, second, day, month, year);

    // Display date as "Today" or "Tomorrow" if applicable
    if (day == timeZone.day() && month == timeZone.month() && year == timeZone.year()) {
        return "Today, " + timeZone.dateTime(timeZone.tzTime(time, UTC_TIME), "H:i");
    } else if (day == timeZone.day() + 1 && month == timeZone.month() && year == timeZone.year()) {
        return "Tomorrow, " + timeZone.dateTime(timeZone.tzTime(time, UTC_TIME), "H:i");
    }

    // Else display the date with the day of the week
    return timeZone.dateTime(timeZone.tzTime(time, UTC_TIME), "D d M H:i");
}


// ---------------------------------- DateTime ----------------------------------

/**
 * Constructor for the DateTime class which is used to store the date and time as strings.
 *
 * @param dateTime The RtcDateTime object to use for this DateTime object.
 */
TimeManager::DateTime::DateTime(RtcDateTime dateTime) {
    char dateString[CHARACTERS_PER_LINE];
    char timeString[CHARACTERS_PER_LINE];

    sprintf(dateString, "%02u/%02u/%04u", dateTime.Day(), dateTime.Month(), dateTime.Year());

    sprintf(timeString, "%02d:%02d:%02d", dateTime.Hour(), dateTime.Minute(), dateTime.Second());

    this->date = String(dateString);
    this->time = String(timeString);
}
