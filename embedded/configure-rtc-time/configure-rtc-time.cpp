/*
 * Configure the time of the RTC module. This is done by setting the time of the
 * module to the time of the compilation of the code. This is done by using the
 * __DATE__ and __TIME__ macros.
 *
 * @author Michael C. Miller (Makuna)
 * @editor F.S. Koulen
 * @date 2023-07-27
 */


#include <Arduino.h>
#include <RtcDS1302.h>

// CONNECTIONS:
// DS1302 CLK/SCL --> 15
// DS1302 DAT/IO --> 13
// DS1302 RST/CE --> 12
// DS1302 VCC --> 3.3v
// DS1302 GND --> GND


ThreeWire myWire(13, 15, 12); // IO (DAT), SCL (CLK), CE (RST)
RtcDS1302<ThreeWire> Rtc(myWire);


#define countOf(a) (sizeof(a) / sizeof(a[0])) // countOf is a macro that returns the number of elements in an array

/**
 * Print the date and time to the serial monitor.
 *
 * @param dateTime The date and time to print.
 */
void printDateTime(const RtcDateTime &dateTime) {
    char dateString[26];

    snprintf_P(dateString,
               countOf(dateString),
               PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
               dateTime.Month(),
               dateTime.Day(),
               dateTime.Year(),
               dateTime.Hour(),
               dateTime.Minute(),
               dateTime.Second());
    Serial.print(dateString);
}

void setup() {
    char compiledDate[12] = __DATE__;
    char compiledTime[9] = __TIME__;
    Serial.begin(57600);

    Serial.println();
    Serial.print("compiled: ");
    Serial.print(compiledDate);
    Serial.println(compiledTime);

    Rtc.Begin();
    // To set the date and time manually, uncomment the following line and
    // replace the date and time with the desired values. The format is
    // "MMM DD YYYY", "HH:MM:SS". Then upload the code and press the reset
    // button when the desired date time is reached to set the RTC time.

    // Rtc.SetDateTime(RtcDateTime("Sep 27 2023", "22:41:30"));

    RtcDateTime compiled = RtcDateTime(compiledDate, compiledTime);
    printDateTime(compiled);
    Serial.println();

    if (!Rtc.IsDateTimeValid()) {
        // Common Causes:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing

        Serial.println("RTC lost confidence in the DateTime!");
        Rtc.SetDateTime(compiled);
    }

    if (Rtc.GetIsWriteProtected()) {
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }

    if (!Rtc.GetIsRunning()) {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    } else if (now > compiled) {
        Serial.println("RTC is newer than compile time. (this is expected)");
    } else if (now == compiled) {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }
}


void loop() {
    RtcDateTime now = Rtc.GetDateTime();

    printDateTime(now);
    Serial.println();

    if (!now.IsValid()) {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
    }

    delay(1000); // one second
}