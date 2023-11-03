# System Requirements

| Requirement ID#      | Requirement                                                                                                                                                  | MoSCoW | Compliant |
|----------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------|--------|-----------|
| [EMBRQ#01](#embrq01) | Embedded device sends measured sensor data to the application backend over http or https.                                                                    | MUST   | YES       |
| [EMBRQ#02](#embrq02) | Embedded device receives or retrieves status messages from the application backend over http or https.                                                       | MUST   | YES       |
| [EMBRQ#03](#embrq03) | The embedded device contains at least two input sensors (e.g. LDR, buttons, joystick, capacitive touch, etc.).                                               | MUST   | YES       |
| [EMBRQ#04](#embrq04) | The embedded device contains at least two visual and/or sensory outputs (e.g. LED, LED Matrix, 7-segment display, motor, servo, actuator, LCD-screen, etc.). | MUST   | YES       |
| [EMBRQ#05](#embrq05) | The embedded device uses the Wi-Fi manager for configuration of SSID, User ID (UID) and Password (PWD) for connecting to the network.                        | MUST   | YES       |

## EMBRQ#01

> Embedded device sends measured sensor data to the application backend over http or https.

The embedded device sends the measured temperature and humidity from the KY-015 sensor to the application backend. The
data is sent to the application backend using a POST request. The data is sent in JSON format. The JSON data
contains the temperature and humidity data & is sent to the application backend using the **HTTPS** protocol.

Code:

```cpp title="embedded/main/Hygrometer.cpp"
/**
 * Post a measurement to the API. Print the response to the serial monitor.
 * If the temperature or humidity is invalid, return 0.
 * Else, return the HTTP code of the response.
 *
 * @param temperature the temperature to post, in degrees Celsius with one decimal place.
 * @param humidity the humidity to post, in percent.
 * @return The HTTP code of the response or 0 if the temperature or humidity is invalid
 */
int Hygrometer::postMeasurement() {
    float temperature = readTemperature();
    int humidity = readHumidity();

    // If the temperature or humidity is invalid, return 0
    if (!checkValidityOfReadings(temperature, humidity)) return 0;

    // Initialize a wi-fi client & http client
    WiFiClientSecure client = httpsClient->getClient();
    HTTPClient httpClient;

    // Set the URL of where the call should be made to.
    httpClient.begin(client, String(BASE_URL) + API_POST_MEASUREMENT);

    // Set the content-type header
    httpClient.addHeader("Content-Type", "application/json");

    // Custom header to tell the tunnel that we don't want to see the screen
    httpClient.addHeader("X-Pinggy-No-Screen", "true");
    httpClient.addHeader("Bypass-Tunnel-Reminder", "false");

    // Create the JSON-object
    jsonBuffer.clear();
    JsonObject root = jsonBuffer.to<JsonObject>();
    root["temperature"] = temperature;
    root["humidity"] = humidity;

    // Serialize the JSON-object to a string
    String body;
    serializeJson(root, body);

    Serial.println("[HTTPS] POST... " + String(BASE_URL) + API_POST_MEASUREMENT);

    // Make the POST-request, this returns the HTTP-code.
    int httpCode = httpClient.POST(body);

    Serial.println("[HTTPS] POST... done with code " + String(httpCode));

    // If the HTTP code is an error code from the HTTPClient, print the error.
    if (HTTPClient::errorToString(httpCode) != String()) {
        Serial.printf("[HTTPS] POST... failed, error: %s\n", HTTPClient::errorToString(httpCode).c_str());
    } else { // Else, check the response
        String payload = httpClient.getString();
        jsonBuffer.clear();
        deserializeJson(jsonBuffer, payload);
        String message = jsonBuffer["message"];

        Serial.printf("[HTTPS] POST... code: %d\n", httpCode);
        // If the message is not null, print the message
        if (message != "null") {
            Serial.println(message);
        } else { // Else, print the HTTP code
            Serial.printf("[HTTPS] POST... failed, error (%d)\n", httpCode);
        }
    }

    return httpCode;
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

The server itself is in these code snippets not served over **HTTPS**. This is because the embedded device runs out of
memory when the server is served over **HTTPS**. This is because the ESP8266 has a very limited amount of memory. If the
server is served over **HTTPS**, the embedded device runs out of memory and crashes. This is why I have chosen to serve
the server over **HTTP**.

However, you can see
in [this](https://gitlab.fdmci.hva.nl/IoT/2023-2024-semester-1/individual-project/iot-koulenf/-/commit/bc07eba905bc2a3f8795a1e93caff3479486cdd5){:target="_blank"}
and [this](https://gitlab.fdmci.hva.nl/IoT/2023-2024-semester-1/individual-project/iot-koulenf/-/commit/24dbc3063436d14857229a5dcc648e9b9f03ce4c){:target="_blank"}
commit that I have two different branches with working code for serving the server over **HTTPS**. However, this code is
not used in the final
product because it would cause the embedded device to crash which would make the product unusable.

That concludes the implementation of the embedded device receiving or retrieving status messages from the application
backend over http or https.

## EMBRQ#03

> The embedded device contains at least two input sensors (e.g. LDR, buttons, joystick, capacitive touch, etc.).

The embedded device contains the following input sensors:

### 1. Button to show next bit of information

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

### 2. Button to show Pac-Man and make sound

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

### 3. Temperature and humidity sensor to measure temperature and humidity

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

### 4. RTC to provide and keep track of time

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

### 1. LCD screen to display information

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

### 2. Servo motor to move Pac-Man

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

### 3. Buzzer to play sound

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

> The embedded device uses the Wi-Fi manager for configuration of SSID, User ID (UID) and Password (PWD) for connecting
> to the network.


To fulfill this requirement, the embedded device uses the [Wi-Fi manager library](https://github.com/tzapu/WiFiManager).
The Wi-Fi manager library is used to
automatically connect the embedded device to the last known Wi-Fi network. If the embedded device fails to connect to
the last known Wi-Fi network, the embedded device will start a Wi-Fi access point. The user can then connect to the
Wi-Fi access point and configure the Wi-Fi network to connect to. The embedded device will then connect to the
configured Wi-Fi network. The code will continue to run after the embedded device has connected to the Wi-Fi network. By
doing this the embedded device uses the Wi-Fi manager library for configuration of SSID and Password (PWD)
to authenticate and connect to the network over **HTTPS**.

!!! info
    In both the provided tutorial and the documentation
    of [tzapu's Wi-Fi manager library](https://github.com/tzapu/WiFiManager),
    there is no mention of configuring the User ID (UID) of the Wi-Fi network. After messaging Dolinde about this,
    she forwarded my message to Gerald who responded that if there is no mention of configuring the User ID (UID) through
    the Wi-Fi Manager, it might not be required to implement this, and it is probably a typo in the
    requirement. Therefore, there is no implementation of configuring the User ID (UID) in the code.

Code:

```cpp title="embedded/main/InternetManager.cpp"
/**
 * Initialize the Wi-Fi connection and set up the web server.
 *
 * @param givenScreen   The screen to use for displaying messages.
 * @param givenStateManager    The state manager to use for posting the current measurement.
 */
void InternetManager::initialize(Screen *givenScreen, StateManager *givenStateManager) {
    // ...
    screen->printText("Initializing", "Wi-Fi connection");
    // Try to connect to the Wi-Fi network
    WiFiManager wifiManager;

    wifiManager.autoConnect(WIFI_SSID, WIFI_PASSWORD);

    Serial.println("Connected to Wi-Fi.");
    screen->printText("Connected to", "Wi-Fi.");
    // ...
}
```


