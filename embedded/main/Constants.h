#ifndef CONSTANTS_H
#define CONSTANTS_H

// --------------------- Configuration
#define SERIAL_BAUD_RATE 115200

#define WIFI_SSID      "iotroam"
#define WIFI_PASSWORD  "OQqcD8LpM7"

#define JSON_BUFFER_SIZE 1024

#define API_READ_APPOINTMENTS "http://koulenf.loca.lt/api/appointment/read.php"

#define LCD_ADDRESS 0x27
#define CHARACTERS_PER_LINE 16
#define NUMBER_OF_LINES 2

#define DHT_TYPE DHT11 // Temperature & Humidity Sensor KY-015 is type DHT11

// --------------------- PINS
#define RTC_CLK_PIN 15
#define RTC_DAT_PIN 13
#define RTC_RST_PIN 12
#define DHT_PIN     2   // Temperature & Humidity Sensor Pin
#define NEXT_BUTTON_PIN  14

#endif //CONSTANTS_H
