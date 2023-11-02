---
title: Hygrometer
summary: Represents a hygrometer that measures the temperature and humidity of the air. 

---

# Hygrometer



Represents a hygrometer that measures the temperature and humidity of the air.  [More...](#detailed-description)


`#include <Hygrometer.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[Hygrometer](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_hygrometer/#function-hygrometer)**(DHT sensor)<br>Implementation of the [Hygrometer](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_hygrometer/) class.  |
| void | **[setScreen](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_hygrometer/#function-setscreen)**([Screen](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_screen/) * screen)<br>Set the screen to use for displaying the state.  |
| void | **[displayState](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_hygrometer/#function-displaystate)**()<br>Display the current state of the DHT sensor on the LCD screen.  |
| int | **[postMeasurement](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_hygrometer/#function-postmeasurement)**()<br>Post a measurement to the API.  |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| const int | **[UPDATE_INTERVAL](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_hygrometer/#variable-update_interval)** <br>The interval in which the state is displayed on the LCD screen, in milliseconds.  |

## Detailed Description

```cpp
class Hygrometer;
```

Represents a hygrometer that measures the temperature and humidity of the air. 

**Author**: F.S. Koulen

The measurements can be sent to the API and displayed on the LCD screen. It uses the DHT sensor to measure the temperature and humidity.


License: GNU GPL v3 

## Public Functions Documentation

### function Hygrometer

```cpp
explicit Hygrometer(
    DHT sensor
)
```

Implementation of the [Hygrometer](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_hygrometer/) class. 

**Parameters**: 

  * **pin** The pin to which the DHT sensor is connected 
  * **dhtType** The type of the DHT sensor 


**Author**: F.S. Koulen

Contains methods to read the temperature and humidity, display the state on the LCD screen and post a measurement to the API.


License: GNU GPLv3 

 Constructor of the [Hygrometer](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_hygrometer/) class. Create a new [Hygrometer](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_hygrometer/) instance and initialize the DHT sensor and JSON buffer.


### function setScreen

```cpp
void setScreen(
    Screen * screen
)
```

Set the screen to use for displaying the state. 

**Parameters**: 

  * **givenScreen** The screen to use for displaying the state 


### function displayState

```cpp
void displayState()
```

Display the current state of the DHT sensor on the LCD screen. 

### function postMeasurement

```cpp
int postMeasurement()
```

Post a measurement to the API. 

**Parameters**: 

  * **temperature** the temperature to post, in degrees Celsius with one decimal place. 
  * **humidity** the humidity to post, in percent. 


**Return**: The HTTP code of the response or 0 if the temperature or humidity is invalid 

Print the response to the serial monitor. If the temperature or humidity is invalid, return 0. Else, return the HTTP code of the response.


## Public Attributes Documentation

### variable UPDATE_INTERVAL

```cpp
const int UPDATE_INTERVAL = 15 * 1000;
```

The interval in which the state is displayed on the LCD screen, in milliseconds. 

-------------------------------

Updated on 2023-11-02 at 14:37:01 +0100