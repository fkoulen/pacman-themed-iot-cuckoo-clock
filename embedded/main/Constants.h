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
MIIC2TCCAkKgAwIBAgIUfEZ7s+goCfvJyRrR3WfArbWmPHEwDQYJKoZIhvcNAQEL
BQAwcDELMAkGA1UEBhMCTkwxFjAUBgNVBAgMDU5vcnRoLUhvbGxhbmQxEjAQBgNV
BAcMCUFtc3RlcmRhbTEPMA0GA1UECgwGU2Nob29sMQwwCgYDVQQLDANJb1QxFjAU
BgNVBAMMDTE5Mi4xNjguMS4yNTQwHhcNMjMxMTAzMDAyMTIwWhcNMjQxMTAyMDAy
MTIwWjBwMQswCQYDVQQGEwJOTDEWMBQGA1UECAwNTm9ydGgtSG9sbGFuZDESMBAG
A1UEBwwJQW1zdGVyZGFtMQ8wDQYDVQQKDAZTY2hvb2wxDDAKBgNVBAsMA0lvVDEW
MBQGA1UEAwwNMTkyLjE2OC4xLjI1NDCBnzANBgkqhkiG9w0BAQEFAAOBjQAwgYkC
gYEA7fdZBw0TIroazTJn9keszFnGmilCylqbg6goORHfLQRPEIbYyeUTHPDLhVY7
vt/PHKj+P5d158/0+vl6G8gWtEM+cjDhtodVXFjIrdtU91me4VVDKhpyq3VO8klx
j5kBQSDmpIN794BSzedihkysDlJo3EAJYdTJXajU7Z9yNAUCAwEAAaNwMG4wHQYD
VR0OBBYEFEGoNuEouVVV2F4cYihDlKSUAhjaMB8GA1UdIwQYMBaAFEGoNuEouVVV
2F4cYihDlKSUAhjaMA8GA1UdEwEB/wQFMAMBAf8wGwYDVR0RBBQwEoIQSVA6MTky
LjE2OC4xLjI1NDANBgkqhkiG9w0BAQsFAAOBgQDDvjMBP8NCHZv0q2uO77dHKI10
F4bFLdQio/4kfhby53LfdEADL1gF/XTOqJB8J8KlLFJ7/fc0d1qW4bpYFQyaJiQE
ducWScd23mRcEMexjYVewO+fEkpMiBsFhn6YOHS6TtRqm6AEpgp+WMltUf24jI6L
Q3MBl697Fz31q8VLQA==
-----END CERTIFICATE-----
)EOF";

static const char serverKey[] PROGMEM =  R"EOF(
-----BEGIN PRIVATE KEY-----
MIICdwIBADANBgkqhkiG9w0BAQEFAASCAmEwggJdAgEAAoGBAO33WQcNEyK6Gs0y
Z/ZHrMxZxpopQspam4OoKDkR3y0ETxCG2MnlExzwy4VWO77fzxyo/j+XdefP9Pr5
ehvIFrRDPnIw4baHVVxYyK3bVPdZnuFVQyoacqt1TvJJcY+ZAUEg5qSDe/eAUs3n
YoZMrA5SaNxACWHUyV2o1O2fcjQFAgMBAAECgYEA6qxA+bklI9wQTkflSnTIrgXi
22jRWykbsCyG7jD3vDdBmXTCGeh0ftfgfS/bX5LrdsIZabD+L4tfdpnMl9UsvNWo
uqNk0MBiY1QLHl0czEDm45JCad0GKLWnQmYbRbBMa70NvAB/rWWjS28DAB9pX97h
bIZb2967pn23FU27hwECQQD7JpiCaewnF0jpik47HvkE1/fSSojq7gAmmdZMEBXC
qIZr5hW/3dYYstti0YS/NT5cko/erlNh0sfVCbeDM8/lAkEA8o+VH7cgYWsZDrZL
oTZgUd122gjEK+XVcgYgqpC3OgluBiQ9/4yNTCYD69obH4xQx3rxqoekAaoX5L2c
93FRoQJBAIeo6WhIXs8evLupgWhd6pS7M5nbuOltdZdkMWUUqyxia3mM5uKkqSje
M7LFCbdewzit0hiugUut11Mz1HSCYCECQEntJOADqiTGxV5MhQRfVD/fJYgSP+e5
JrKX14DkllNj6FqK1TJ7ndzlgTByyu10kHIbsGfu6zdupdWbTKnFqcECQGoUGXFN
9nh9FqYaSeE6mD8St1/+52PUklFxDXorBPCxpMKvKCdS+f0wpPJ+/072Gkcj+4i+
OtWFnRfYFaSQel0=
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
