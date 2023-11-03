/**
 * This file contains all the constants used in the project.
 * It is used to store all the constants in one place and to make them easy to change.
 *
 * @author F.S. Koulen
 * @details License: GNU GPLv3
 */

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
//#define FINGERPRINT             "CC 6F 43 C4 19 B8 17 28 E8 86 05 7B 9D B4 B4 D4 AC 26 C3 E3";
// The fingerprint can then be set like this:
//    char fingerprint[] = FINGERPRINT
//    client.setFingerprint(fingerprint);

/**
 * The fingerprint of the certificate of the API.
 * Instructions on how to get the certificate:
 * @see https://randomnerdtutorials.com/esp8266-nodemcu-https-requests/#getting-server-certificate
 */
const char IRG_Root_X1[] PROGMEM = R"CERT(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)CERT";

/**
 * Instructions on how to create these can be found here:
 *
 * https://www.onetransistor.eu/2019/04/https-server-on-esp8266-nodemcu.html
 */
static const char serverCert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIC3jCCAkegAwIBAgIUaKygDLLkKZkT1AqgZAZml+JQ7V8wDQYJKoZIhvcNAQEL
BQAwcTELMAkGA1UEBhMCTkwxFjAUBgNVBAgMDU5vcnRoLUhvbGxhbmQxEjAQBgNV
BAcMCUFtc3RlcmRhbTEQMA4GA1UECgwHU2Nob29sXTEMMAoGA1UECwwDSW9UMRYw
FAYDVQQDDA1lc3A4MjY2LmxvY2FsMB4XDTIzMTEwMjE1MTUyOFoXDTI0MTEwMTE1
MTUyOFowcTELMAkGA1UEBhMCTkwxFjAUBgNVBAgMDU5vcnRoLUhvbGxhbmQxEjAQ
BgNVBAcMCUFtc3RlcmRhbTEQMA4GA1UECgwHU2Nob29sXTEMMAoGA1UECwwDSW9U
MRYwFAYDVQQDDA1lc3A4MjY2LmxvY2FsMIGfMA0GCSqGSIb3DQEBAQUAA4GNADCB
iQKBgQDNG0FtPhCB94d9Uo+5b5BHiScOE5Tu2+pO4kdEc4LOeLu+2KjKZxMDm/Om
BTDIekrPmmryz0Hy8QoxRw2GrlwqrTCJlElkx0ILJjrIjqct00BY4qDykrBeipiE
VUEXO/8DOADtRWulzWeMR7bm+iGeI2NMd8VqapwQ+hQumbPQrQIDAQABo3MwcTAd
BgNVHQ4EFgQUObW8fiHbS3Q1jpHgg+DQBS67m3UwHwYDVR0jBBgwFoAUObW8fiHb
S3Q1jpHgg+DQBS67m3UwDwYDVR0TAQH/BAUwAwEB/zAeBgNVHREEFzAVgg1lc3A4
MjY2LmxvY2FshwTAqAH+MA0GCSqGSIb3DQEBCwUAA4GBAKTlo2wI+RwiK60KROrw
FE3CKikr8RKG9g4DMLhkORJ4ON5sEbXalP6phKVZhAtZYe/SBS2GMkn/abk4Bm6d
a2/HUIhpyeIYgbws9KXDVTSW8U37zwiPO2nCtYSsLcbeGcoSkwx95SsLnuDfJVri
ggaYlaEN7AD8TR1hsNA47GOJ
-----END CERTIFICATE-----
)EOF";

static const char serverKey[] PROGMEM =  R"EOF(
-----BEGIN PRIVATE KEY-----
MIICeAIBADANBgkqhkiG9w0BAQEFAASCAmIwggJeAgEAAoGBAM0bQW0+EIH3h31S
j7lvkEeJJw4TlO7b6k7iR0Rzgs54u77YqMpnEwOb86YFMMh6Ss+aavLPQfLxCjFH
DYauXCqtMImUSWTHQgsmOsiOpy3TQFjioPKSsF6KmIRVQRc7/wM4AO1Fa6XNZ4xH
tub6IZ4jY0x3xWpqnBD6FC6Zs9CtAgMBAAECgYEAgD/BqmA7jDjN1JQSYH4c9k4R
SKD/6FdEbGza6TddHGOr6YqqCF1pK0GRmUb3mPO24ZcJtqfX8eO8XtGx6HwQDlSv
PYzv9g0n3MVRTswQQXaELyOcr7JeUnlRFHVG/D4yxXSCmhgHemn8F/cDdOClsq8e
BCbDXqx0h+LOXOV+FYECQQDrfC2hGQp8iRbAmOnK8TTvy1ES+VK2Gdhxr5+pzFvQ
uSajaNNUDTg1Q8AqevTaV+hyZnrk1SM/iBEPRptdxEnNAkEA3vmRwVCoEuYfJqrS
UWUQDd71YitOIWfr4jNNyzNz8ERyGmNScaZHjYQ/JDQLPKPDRHiVpZughYwhGx9w
Y4FCYQJBAK+C+EdP8J7tVkXqMqaNrNTlBuJLbbhH/yiMq0XVCMHCnefBY3EMAU7B
1mJTDlgGmTta4lHYAdOCSKTIDViPyikCQQC8W1L3XO0+WctC3NaiD5+KOChN74sm
ySUIhpJW73YnJ4rEI9cHTpHvSCIWsSg055oSg1LW/SqS5hcpVFuakxzBAkBrsuvA
g56P8LsfBENVI5QPg4EB7hvr0KhxSX09uXBIBGfQwbgVGmwtzuoPZYBZBAJh0h1L
OsMBDHcntU0OUbxz
-----END PRIVATE KEY-----
)EOF";

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
