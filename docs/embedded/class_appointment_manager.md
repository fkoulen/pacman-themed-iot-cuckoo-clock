---
title: AppointmentManager
summary: Represents an appointment manager that is responsible for fetching, storing and displaying appointments. 

---

# AppointmentManager



Represents an appointment manager that is responsible for fetching, storing and displaying appointments.  [More...](#detailed-description)


`#include <AppointmentManager.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[AppointmentManager](/embedded/class_appointment_manager/#function-appointmentmanager)**()<br>Implementation of the [AppointmentManager](/embedded/class_appointment_manager/) class.  |
| void | **[setScreen](/embedded/class_appointment_manager/#function-setscreen)**([Screen](/embedded/class_screen/) * screen)<br>Set the screen to use for displaying the appointments.  |
| void | **[fetch](/embedded/class_appointment_manager/#function-fetch)**()<br>Connect to the API and store all appointments if the connection is successful.  |
| void | **[displayState](/embedded/class_appointment_manager/#function-displaystate)**()<br>Display how many appointments are found on the LCD.  |
| bool | **[displayNextAppointment](/embedded/class_appointment_manager/#function-displaynextappointment)**([TimeManager](/embedded/class_time_manager/) timeManager)<br>Display the next appointment on the LCD.  |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| const int | **[UPDATE_INTERVAL](/embedded/class_appointment_manager/#variable-update_interval)** <br>The update interval for when the screen should be updated.  |

## Detailed Description

```cpp
class AppointmentManager;
```

Represents an appointment manager that is responsible for fetching, storing and displaying appointments. 

**Author**: F.S. Koulen

It uses the [Screen](/embedded/class_screen/) class to display the appointments on the LCD. The appointments are fetched from the API and stored in a JSON array.


License: GNU GPLv3 

## Public Functions Documentation

### function AppointmentManager

```cpp
AppointmentManager()
```

Implementation of the [AppointmentManager](/embedded/class_appointment_manager/) class. 

**Author**: F.S. Koulen

It has methods to fetch, store and display appointments.


License: GNU GPLv3 

 Constructor of the [AppointmentManager](/embedded/class_appointment_manager/) class. It initializes the JSON buffer with the correct size. 


### function setScreen

```cpp
void setScreen(
    Screen * screen
)
```

Set the screen to use for displaying the appointments. 

**Parameters**: 

  * **givenScreen** The screen to use for displaying the appointments 


### function fetch

```cpp
void fetch()
```

Connect to the API and store all appointments if the connection is successful. 

If the connection is not successful, show an error message on the LCD. 


### function displayState

```cpp
void displayState()
```

Display how many appointments are found on the LCD. 

### function displayNextAppointment

```cpp
bool displayNextAppointment(
    TimeManager timeManager
)
```

Display the next appointment on the LCD. 

**Parameters**: 

  * **timeManager** The [TimeManager](/embedded/class_time_manager/) to use for converting the UTC time to local time 


**Return**: True if there is a next appointment to display, false otherwise 

If there is no next appointment to display, return false.


## Public Attributes Documentation

### variable UPDATE_INTERVAL

```cpp
const int UPDATE_INTERVAL = 60 * 1000;
```

The update interval for when the screen should be updated. 

It is set to 1 minute since the display will be back to the time display after 15 seconds. This means that the appointment will be displayed for 15 seconds at most and the screen does not need to be updated more often than that. 


-------------------------------

Updated on 2023-11-02 at 13:07:21 +0100