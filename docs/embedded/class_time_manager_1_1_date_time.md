---
title: TimeManager::DateTime
summary: Represents the date and time in a readable format. 

---

# TimeManager::DateTime



Represents the date and time in a readable format.  [More...](#detailed-description)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[DateTime](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager_1_1_date_time/#function-datetime)**(RtcDateTime dateTime)<br>Constructor for the [DateTime](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager_1_1_date_time/) class which is used to store the date and time as strings.  |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| String | **[date](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager_1_1_date_time/#variable-date)** <br>Holds the date.  |
| String | **[time](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager_1_1_date_time/#variable-time)** <br>Holds the time.  |

## Detailed Description

```cpp
class TimeManager::DateTime;
```

Represents the date and time in a readable format. 

This makes it easier to display the date and time on the screen. 

## Public Functions Documentation

### function DateTime

```cpp
explicit DateTime(
    RtcDateTime dateTime
)
```

Constructor for the [DateTime](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager_1_1_date_time/) class which is used to store the date and time as strings. 

**Parameters**: 

  * **dateTime** The RtcDateTime object to use for this [DateTime](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_time_manager_1_1_date_time/) object. 


## Public Attributes Documentation

### variable date

```cpp
String date;
```

Holds the date. 

### variable time

```cpp
String time;
```

Holds the time. 

-------------------------------

Updated on 2023-11-02 at 14:37:01 +0100