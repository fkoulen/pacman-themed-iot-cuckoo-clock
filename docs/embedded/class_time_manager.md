---
title: TimeManager
summary: Represents the manager for displaying the time and date and converting UTC time to local time. 

---

# TimeManager



Represents the manager for displaying the time and date and converting UTC time to local time.  [More...](#detailed-description)


`#include <TimeManager.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[TimeManager](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager/#function-timemanager)**(RtcDS1302< ThreeWire > rtc)<br>Implementation of the [TimeManager](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager/) class.  |
| void | **[initialize](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager/#function-initialize)**([Screen](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_screen/) * screen)<br>Initialize the [TimeManager](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager/) object by setting the screen to use for displaying the time and initializing the RTC.  |
| void | **[displayTime](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager/#function-displaytime)**()<br>Display the current date and time on the screen.  |
| void | **[updateDateTime](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager/#function-updatedatetime)**()<br>Update the time on the screen instead of clearing the screen and redrawing the time.  |
| RtcDateTime | **[getDateTime](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager/#function-getdatetime)**()<br>Get the current date and time.  |
| String | **[convertUTCtoLocalTime](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager/#function-convertutctolocaltime)**(const String & utcTime)<br>Convert the given UTC time to local time.  |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| const int | **[UPDATE_INTERVAL](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager/#variable-update_interval)** <br>The interval in milliseconds to update the time display.  |

## Detailed Description

```cpp
class TimeManager;
```

Represents the manager for displaying the time and date and converting UTC time to local time. 

**Author**: F.S. Koulen


License: GNU GPLv3 

## Public Functions Documentation

### function TimeManager

```cpp
explicit TimeManager(
    RtcDS1302< ThreeWire > rtc
)
```

Implementation of the [TimeManager](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager/) class. 

**Parameters**: 

  * **rtc** The RTC object to use for getting the current date and time 


**Author**: F.S. Koulen

This class is used to display the time on the LCD screen and to convert UTC time to local time.


License: GNU GPLv3 

 Constructor for the [TimeManager](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager/) class. Creates a [TimeManager](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager/) object and initializes the RTC object to use for getting the current date and time.


### function initialize

```cpp
void initialize(
    Screen * screen
)
```

Initialize the [TimeManager](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager/) object by setting the screen to use for displaying the time and initializing the RTC. 

**Parameters**: 

  * **givenScreen** The screen to use for displaying the time 


This method also waits for the NTP sync to complete and sets the RTC time to the NTP time. The NTP time is converted to the local time zone before setting the RTC time. The RTC is then locked for writing.


### function displayTime

```cpp
void displayTime()
```

Display the current date and time on the screen. 

### function updateDateTime

```cpp
void updateDateTime()
```

Update the time on the screen instead of clearing the screen and redrawing the time. 

**See**: [displayTime()](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager/#function-displaytime)

This is used to prevent flickering. Should only be called if [displayTime()](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager/#function-displaytime) has been called before.


### function getDateTime

```cpp
RtcDateTime getDateTime()
```

Get the current date and time. 

**Return**: The current date and time 

### function convertUTCtoLocalTime

```cpp
String convertUTCtoLocalTime(
    const String & utcTime
)
```

Convert the given UTC time to local time. 

**Parameters**: 

  * **utcTime** The UTC time to convert 


**Return**: The local time 

## Public Attributes Documentation

### variable UPDATE_INTERVAL

```cpp
const int UPDATE_INTERVAL = 1000;
```

The interval in milliseconds to update the time display. 

This is set to 1000 milliseconds, so the time display is updated every second. 


-------------------------------

Updated on 2023-11-02 at 14:37:01 +0100