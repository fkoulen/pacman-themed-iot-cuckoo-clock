#ifndef CONSTANTS_H
#define CONSTANTS_H

// Provide official timezone names
// https://en.wikipedia.org/wiki/List_of_tz_database_time_zones

#define TIME_ZONE               "Europe/Amsterdam"

// --------------------- Configuration
#define SERIAL_BAUD_RATE 115200

//#define WIFI_SSID               "iotroam"
//#define WIFI_PASSWORD           "OQqcD8LpM7"

#define WIFI_SSID               "iot-koulenf"
#define WIFI_PASSWORD           "iot2023"


// --------------------- API
// You can get the fingerprint of the API by running the following command in bash:
// echo | openssl s_client -connect koulenf.loca.lt:443 |& openssl x509 -fingerprint -noout | awk -F= '{print $2}' | tr -d ':' | sed 's/../& /g'
#define FINGERPRINT             "BB 6D 47 85 E9 84 C9 A6 7B E5 2D AC 67 EB 9F C9 26 85 F9 C4";
#define JSON_BUFFER_SIZE        1024
#define BASE_URL                "https://koulenf.loca.lt/"
#define API_READ_APPOINTMENTS   "api/appointment/read_next_7_days.php"
#define API_POST_MEASUREMENT    "api/measurement/create.php"

// --------------------- Cuckoo Mechanism
#define START_NIGHT_MODE       22
#define END_NIGHT_MODE         7

// --------------------- LCD
#define LCD_ADDRESS             0x27
#define CHARACTERS_PER_LINE     16
#define NUMBER_OF_LINES         2
#define TIME_TO_SHOW_MESSAGE    3000

// --------------------- DHT
#define DHT_TYPE                DHT11 // Temperature & Humidity Sensor KY-015 is type DHT11

// --------------------- PINS
#define RTC_CLK_PIN             15
#define RTC_DAT_PIN             13
#define RTC_RST_PIN             12
#define DHT_PIN                 2   // Temperature & Humidity Sensor Pin
#define NEXT_BUTTON_PIN         16
#define PLAY_BUTTON_ANALOG_PIN  A0
#define BUZZER_PIN              14
#define SERVO_PIN               0

#endif //CONSTANTS_H
