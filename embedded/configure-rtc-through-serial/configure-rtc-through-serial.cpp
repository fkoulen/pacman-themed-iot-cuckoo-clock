/*
 * Configure the RTC through the serial monitor
 *
 * @author Jan Mallari
 * @see https://www.circuitbasics.com/how-to-use-a-real-time-clock-module-with-the-arduino/
 * @editor F.S. Koulen
 * @updated 2023-10-03
 */

#include <Arduino.h>
#include <Wire.h>                   // for I2C communication
#include <LiquidCrystal_I2C.h>      // for LCD
#include <RtcDS1302.h>              // for RTC

LiquidCrystal_I2C lcd(0x27, 16, 2); // create LCD with I2C address 0x27, 16 characters per line, 2 lines

ThreeWire myWire(13, 15, 12); // IO (DAT), SCL (CLK), CE (RST)
RtcDS1302<ThreeWire> rtc(myWire);


/*
   function to update RTC time using user input
*/
void updateRTC() {

    lcd.clear();  // clear LCD
    lcd.setCursor(0, 0);
    lcd.print("Edit Mode...");

    // ask user to enter new date and time
    const char txt[6][15] = {"year [4-digit]", "month [1~12]", "day [1~31]",
                             "hours [0~23]", "minutes [0~59]", "seconds [0~59]"};
    String str = "";
    long newDate[6];

    while (Serial.available()) {
        Serial.read();  // clear serial buffer
    }

    for (int i = 0; i < 6; i++) {

        Serial.print("Enter ");
        Serial.print(txt[i]);
        Serial.print(": ");

        while (!Serial.available()) { ; // wait for user input
        }

        str = Serial.readString();  // read user input
        newDate[i] = str.toInt();   // convert user input to number and save to array

        Serial.println(newDate[i]); // show user input
    }

    // update RTC
    rtc.SetDateTime(RtcDateTime(newDate[0], newDate[1], newDate[2], newDate[3], newDate[4], newDate[5]));
    Serial.println("RTC Updated!");
}

/*
   function to update LCD text
*/
void updateLCD() {

    /*
       create array to convert digit days to words:

       0 = Sunday    |   4 = Thursday
       1 = Monday    |   5 = Friday
       2 = Tuesday   |   6 = Saturday
       3 = Wednesday |
    */
    const char dayInWords[7][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

    /*
       create array to convert digit months to words:

       0 = [no use]  |
       1 = January   |   6 = June
       2 = February  |   7 = July
       3 = March     |   8 = August
       4 = April     |   9 = September
       5 = May       |   10 = October
       6 = June      |   11 = November
       7 = July      |   12 = December
    */
    const char monthInWords[13][4] = {" ", "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
                                      "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

    // get time and date from RTC and save in variables
    RtcDateTime rtcTime = rtc.GetDateTime();

    int ss = rtcTime.Second();
    int mm = rtcTime.Minute();
    int hh = rtcTime.Hour();
    int DD = rtcTime.DayOfWeek();
    int dd = rtcTime.Day();
    int MM = rtcTime.Month();
    int yyyy = rtcTime.Year();

    // move LCD cursor to upper-left position
    lcd.setCursor(0, 0);

    // print date in dd-MMM-yyyy format and day of week
    if (dd < 10) lcd.print("0");  // add preceeding '0' if number is less than 10
    lcd.print(dd);
    lcd.print("-");
    lcd.print(monthInWords[MM]);
    lcd.print("-");
    lcd.print(yyyy);

    lcd.print("  ");
    lcd.print(dayInWords[DD]);

    // move LCD cursor to lower-left position
    lcd.setCursor(0, 1);

    // print time in 12H format
    lcd.print(hh);
    lcd.print(':');

    lcd.print(mm);
    lcd.print(':');

    lcd.print(ss);

}

void setup() {
    Serial.begin(115200); // initialize serial

    lcd.init();       // initialize lcd
    lcd.backlight();  // switch-on lcd backlight

    rtc.Begin();       // initialize rtc
    Serial.println();
    updateRTC();
}


void loop() {
    updateLCD();  // update LCD text
}