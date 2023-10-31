# System Requirements

| Requirement ID#      | Requirement                                                                                                                                                  | MoSCoW | Compliant |
|----------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------|--------|-----------|
| [EMBRQ#01](#embrq01) | Embedded device sends measured sensor data to the application backend over http or https.                                                                    | MUST   | YES       |
| [EMBRQ#02](#embrq02) | Embedded device receives or retrieves status messages from the application backend over http or https.                                                       | MUST   | NO        |
| [EMBRQ#03](#embrq03) | The embedded device contains at least two input sensors (e.g. LDR, buttons, joystick, capacitive touch, etc.).                                               | MUST   | NO        |
| [EMBRQ#04](#embrq04) | The embedded device contains at least two visual and/or sensory outputs (e.g. LED, LED Matrix, 7-segment display, motor, servo, actuator, LCD-screen, etc.). | MUST   | NO        |
| [EMBRQ#05](#embrq05) | The embedded device uses the Wi-Fi manager for configuration of SSID, User ID (UID) en Password (PWD) for connecting to the network.                         | MUST   | NO        |

## EMBRQ#01

> Embedded device sends measured sensor data to the application backend over http or https.

The embedded device sends the measured temperature and humidity from the KY-015 sensor to the application backend. The
data is sent to the application backend using a POST request. The data is sent in JSON format. The JSON data
contains the temperature and humidity data & is sent to the application backend using the **HTTPS** protocol.

Code:

```cpp title="embedded/main/HygroMeter.cpp"
/**
 * Post a measurement to the API. Print the response to the serial monitor.
 *
 * @param temperature
 * @param humidity
 */
void Hygrometer::postMeasurement(float temperature, int humidity) {
}
```

## EMBRQ#02

> Embedded device receives or retrieves status messages from the application backend over http or https.

To fulfill this requirement, the embedded device has been set up as a web server.

```cpp title="embedded/main/InternetManager.cpp"
/**
 * Constructor of the InternetManager class
 */
InternetManager::InternetManager(): jsonBuffer(DynamicJsonDocument(JSON_BUFFER_SIZE)) {
server = new ESP8266WebServer(PORT);
}
```

The web server has multiple endpoints:

* `/` - The root endpoint. This endpoint shows the user that this is url for the web server of the embedded device.
* `/lcd` - The LCD endpoint. This endpoint allows the user to remotely control the backlight of the LCD screen.
* `/measurement` - The measurement endpoint. This endpoint allows the user to request the embedded device to post a new
  measurement to the application backend.

The endpoints are configured in the `intialize` method of the InternetManager class. CORS is enabled for all endpoints
so
that the application frontend can make requests to the embedded device from a different origin.

```cpp title="embedded/main/InternetManager.cpp"
/**
 * Initialize the Wi-Fi connection
 *
 * @param givenScreen   The screen to use
 */
void InternetManager::initialize(Screen *givenScreen, StateManager *givenStateManager) {
// ...

server->on(ROOT, HTTP_GET,[this] {
handleRoot(); });
server->on(LCD, HTTP_POST,[this] { handleLCD(); });
server->on(MEASUREMENT, HTTP_GET,[this] { handleMeasurement(); });
server->onNotFound([this] { handleNotFound(); });
server->enableCORS(true);
server->begin();
Serial.println("Server started.");
}
```

This is the implementation of the `measurement` endpoint:

```cpp title="embedded/main/InternetManager.cpp"
/**
 * Handle the GET request to post a measurement.
 * The measurement is posted to the API and the response is sent back to the client.
 */
void InternetManager::handleMeasurement() {
jsonBuffer.clear();
Serial.println("[Server] Handling measurement request");
int responseCode = stateManager->postMeasurement();
jsonBuffer["response"] = responseCode;
String response;
serializeJson(jsonBuffer, response);
server->send(HTTP_CODE_OK, "application/json", response);
}
``` 

In the main `loop` method of the embedded device, the following method is called to handle incoming requests:

```cpp title="embedded/main/InternetManager.cpp"
/**
 * Handle the server
 */
void InternetManager::listenServer() {
server->handleClient();
}
```

This method tells the server to handle incoming requests.

So when the embedded device receives a request to the `/measurement` endpoint, the `handleMeasurement` method is called.
This method calls the `postMeasurement` method of the `StateManager` class.

```cpp title="embedded/main/StateManager.cpp"
/**
 * Post a measurement to the API. Print the response to the serial monitor.
 * Show that the measurement is being posted on the LCD screen.
 *
 * @return The response code
 */
int StateManager::postMeasurement() {
screen->printText("Posting measure-", "ment to API...");
int response = hygrometer.postMeasurement();
screen->printText("Response code: ", String(response));
delay(TIME_TO_SHOW_MESSAGE);
displayTime();

return response;
}
```

This method calls the `postMeasurement` method of the `Hygrometer` class. You can find the implementation of this
method in the [EMBRQ#01](#embrq01) section. What this method does is post a new measurement to the application backend
and return the response code/status message from the application backend. This is done over the **HTTPS** protocol.
The response code is then sent back to the client.

That concludes the implementation of the embedded device receiving or retrieving status messages from the application
backend over http or https.

## EMBRQ#03

> The embedded device contains at least two input sensors (e.g. LDR, buttons, joystick, capacitive touch, etc.).

The embedded device contains the following input sensors:

### Button to show next bit of information

This button is connected to pin 16 of the ESP8266, which is a digital pin. It is initialized in the `setup` method of
the embedded device.

```cpp title="embedded/main/main.ino"
void setup() {
    pinMode(NEXT_BUTTON_PIN, INPUT);
   // ...
}
```

In the `loop` method of the embedded device, the following method is called to check if the button is pressed:

```cpp title="embedded/main/StateManager.cpp"
/**
 * Check if the button is pressed to switch display mode
 */
void StateManager::checkButtonPress() {
    if (digitalRead(NEXT_BUTTON_PIN) == HIGH) {
        lastButtonPressTime = millis();
        if (!screen->isBacklightOn()) {
            screen->toggleBacklight();
            displayTime();
        } else {
            goToNextDisplayState();
        }
        delay(NEXT_BUTTON_DEBOUNCE_TIME);
    }

    //...
}
```

### Button to show Pac-Man and make sound

This button is connected to pin A0 of the ESP8266, which is an analog pin.

In the `loop` method of the embedded device, the following method is called to check if the button is pressed:

```cpp title="embedded/main/StateManager.cpp"
/**
 * Check if the button is pressed to switch display mode
 */
void StateManager::checkButtonPress() {
    // ...

    // The play button is connected to an analog pin, so we need to use analogRead instead of digitalRead
    // to check if the button is pressed. The button is pressed when the analog value is close to 1024.
    // So we check if the analog value is greater than 1000.
    if (analogRead(PLAY_BUTTON_ANALOG_PIN) > MIN_HIGH_ANALOG_VALUE) {
        executeCuckooMechanism(timeManager.getDateTime());
        changeCurrentDisplayState(TIME);
    }
}
```

### Temperature and humidity sensor to measure temperature and humidity

The KY-015 sensor is used to measure the temperature and humidity. The sensor is connected to the ESP8266 using pin 2.
An object of the `DHT` class is created in the main file. The sensor is then initialized in the Hygrometer constructor.

```cpp title="embedded/main/main.ino"
DHT dht(DHT_PIN, DHT_TYPE);
Hygrometer hygrometer = Hygrometer(dht);
```

```cpp title="embedded/main/Hygrometer.cpp"
/**
 * Constructor of the Hygrometer class.
 * Create a new Hygrometer instance and initialize the DHT sensor.
 *
 * @param pin       The pin to which the DHT sensor is connected
 * @param dhtType   The type of the DHT sensor
 */
Hygrometer::Hygrometer(DHT dht) : dht(dht), jsonBuffer(DynamicJsonDocument(JSON_BUFFER_SIZE)) {
    dht.begin();
    this->dht = dht;
}
```

The values from the sensor are then read through the following methods:

```cpp title="embedded/main/Hygrometer.cpp"
/**
 * Read the temperature from the DHT sensor.
 *
 * @return The temperature in degrees Celsius with one decimal place
 */
float Hygrometer::readTemperature() {
    return dht.readTemperature();
}

/**
 * Read the humidity from the DHT sensor.
 *
 * @return The humidity in percent
 */
int Hygrometer::readHumidity() {
    return static_cast<int>(dht.readHumidity());
}
```

### RTC to provide and keep track of time

The DS1302 module is used to provide and keep track of time. The module is connected to the ESP8266 using the following
pins:

```cpp title="embedded/main/Constants.cpp"
#define RTC_CLK_PIN             15
#define RTC_DAT_PIN             13
#define RTC_RST_PIN             12
```

An ThreeWire object is created in the main file. This object is then passed to the constructor of the TimeManager class.

```cpp title="embedded/main/main.ino"
ThreeWire rtcWiring(RTC_DAT_PIN, RTC_CLK_PIN, RTC_RST_PIN);
TimeManager timeManager = TimeManager(rtcWiring);
```

The RtcDS1302 object is then created in the TimeManager constructor.

```cpp title="embedded/main/TimeManager.cpp"
/**
 * Constructor for the TimeManager class.
 *
 * @param rtc The RTC object to use for getting the time.
 */
TimeManager::TimeManager(RtcDS1302<ThreeWire> rtc) : rtc(rtc) {
}
```

The date and time are then retrieved through the following method:

```cpp title="embedded/main/TimeManager.cpp"
/**
 * Get the current date and time.
 *
 * @return The current date and time
 */
RtcDateTime TimeManager::getDateTime() {
    return rtc.GetDateTime();
}
```

## EMBRQ#04

> The embedded device contains at least two visual and/or sensory outputs (e.g. LED, LED Matrix, 7-segement display,
> motor, servo, actuator, LCD-screen, etc.).

The embedded device contains the following visual and/or sensory outputs:

### LCD screen to display information

The embedded device contains a 16x2 LCD screen to display information. The LCD screen is connected to the ESP8266 and
can be reached on address 0x27. The LCD screen is initialized in the constructor of the Screen class.

```cpp title="embedded/main/Screen.h"
class Screen {
// ...
private:
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(LCD_ADDRESS, CHARACTERS_PER_LINE, NUMBER_OF_LINES);
    // ...
};
```

The screen is then used through the different methods in the Screen class. Check
the [implementation of the Screen class](https://gitlab.fdmci.hva.nl/IoT/2023-2024-semester-1/individual-project/iot-koulenf/-/blob/main/embedded/main/Screen.cpp?ref_type=heads)
for more information.

### Servo motor to move Pac-Man

The servo motor is connected to pin 0 of the ESP8266. It is initialized in the `initialize` method of
the `CuckooMechanism` class.

```cpp title="embedded/main/CuckooMechanism.cpp" 
/**
 * Initialize the cuckoo mechanism by attaching the servo motor and moving it to the starting position.
 * It also sets the screen to use for displaying the cuckoo state and creates the custom characters. 
 * 
 * @param givenScreen The screen to use for displaying the cuckoo state
 */
void CuckooMechanism::initialize(Screen *givenScreen) {
    motor.attach(SERVO_PIN);
    motor.write(SERVO_START_POSITION);
    // ...
}
```

The motor is then moved through the following methods:

```cpp title="embedded/main/CuckooMechanism.cpp"
/**
 * Move the cuckoo forward.
 */
void CuckooMechanism::moveCuckooForward() {
    Serial.println("Moving cuckoo forward.");
    motor.write(SERVO_END_POSITION);
}

/**
 * Move the cuckoo backward.
 */
void CuckooMechanism::moveCuckooBackward() {
    Serial.println("Moving cuckoo backward.");
    motor.write(SERVO_START_POSITION);
}
```

### Buzzer to play sound

The buzzer is connected to pin 14 of the ESP8266. Notes are played on the buzzer in the `playMelody` method of the
`CuckooMechnism` class.

```cpp title="embedded/main/CuckooMechanism.cpp" hl_lines="11 17"
/**
 * Play the Pac-Man melody.
 */
void CuckooMechanism::playMelody() {
   // ...

    for (/.../) {
        // ...

        // Play the note on the buzzer. Only play 90% of the note, to avoid overlapping notes.
        tone(BUZZER_PIN, melody[thisNote], static_cast<int>(noteDurationInMs * NOTE_DURATION_MULTIPLIER));

        // Wait for the specified duration before playing the next note.
        delay(static_cast<int>(noteDurationInMs));

        // Stop playing the note.
        noTone(BUZZER_PIN);
    }
}
```

## EMBRQ#05

> The embedded device uses the Wi-Fi manager for configuration of SSID, User ID (UID) en Password (PWD) for connecting
> to the network.

- [ ] Use Wi-Fi manager to configure SSID, UID and PWD

[Insert text explaining how you fulfilled the requirement here]

Code:

```cpp
// Insert code snippet(s) proving the requirement is fulfilled here
```


