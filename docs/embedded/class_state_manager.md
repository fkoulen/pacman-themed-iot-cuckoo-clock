---
title: StateManager
summary: Represents the manager for the state of the embedded system. 

---

# StateManager



Represents the manager for the state of the embedded system.  [More...](#detailed-description)


`#include <StateManager.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[StateManager](/embedded/class_state_manager/#function-statemanager)**([Screen](/embedded/class_screen/) * screen, [CuckooMechanism](/embedded/class_cuckoo_mechanism/) cuckooMechanism, [TimeManager](/embedded/class_time_manager/) timeManager, [Hygrometer](/embedded/class_hygrometer/) hygrometer, [AppointmentManager](/embedded/class_appointment_manager/) appointments)<br>Initialize the state manager with the given components.  |
| void | **[initialize](/embedded/class_state_manager/#function-initialize)**([Screen](/embedded/class_screen/) * givenScreen)<br>Set the givenScreen for the state manager and its components.  |
| void | **[checkToGoBackToTimeDisplay](/embedded/class_state_manager/#function-checktogobacktotimedisplay)**()<br>Check if it's time to go back to the time display.  |
| void | **[checkToUpdateDisplay](/embedded/class_state_manager/#function-checktoupdatedisplay)**()<br>Check if it's time to update the current display state.  |
| void | **[checkButtonPress](/embedded/class_state_manager/#function-checkbuttonpress)**()<br>Check if the button is pressed to switch display mode.  |
| void | **[checkToActivateCuckooMechanism](/embedded/class_state_manager/#function-checktoactivatecuckoomechanism)**()<br>Check if it's time to activate the cuckoo mechanism.  |
| void | **[displayTime](/embedded/class_state_manager/#function-displaytime)**()<br>Change the display state to TIME and display the time.  |
| int | **[postMeasurement](/embedded/class_state_manager/#function-postmeasurement)**()<br>Post a measurement to the API.  |

## Detailed Description

```cpp
class StateManager;
```

Represents the manager for the state of the embedded system. 

**Author**: F.S. Koulen

This class is responsible for changing the display state, checking for button presses and activating the cuckoo mechanism when needed.


License: GNU GPLv3 

## Public Functions Documentation

### function StateManager

```cpp
StateManager(
    Screen * screen,
    CuckooMechanism cuckooMechanism,
    TimeManager timeManager,
    Hygrometer hygrometer,
    AppointmentManager appointments
)
```

Initialize the state manager with the given components. 

### function initialize

```cpp
void initialize(
    Screen * givenScreen
)
```

Set the givenScreen for the state manager and its components. 

**Parameters**: 

  * **givenScreen** The screen to display the content on for the state manager and its components 


Then change the display state to TIME.


### function checkToGoBackToTimeDisplay

```cpp
void checkToGoBackToTimeDisplay()
```

Check if it's time to go back to the time display. 

If it is, change the display state to TIME. 


### function checkToUpdateDisplay

```cpp
void checkToUpdateDisplay()
```

Check if it's time to update the current display state. 

**Parameters**: 

  * **currentTime** The current time in milliseconds 


If it is, update the display.


### function checkButtonPress

```cpp
void checkButtonPress()
```

Check if the button is pressed to switch display mode. 

### function checkToActivateCuckooMechanism

```cpp
void checkToActivateCuckooMechanism()
```

Check if it's time to activate the cuckoo mechanism. 

If it is, activate the cuckoo mechanism and change the display state to TIME afterward. 


### function displayTime

```cpp
void displayTime()
```

Change the display state to TIME and display the time. 

### function postMeasurement

```cpp
int postMeasurement()
```

Post a measurement to the API. 

**Return**: The response code of the POST request 

Print the response to the serial monitor. Show that the measurement is being posted on the LCD screen.


-------------------------------

Updated on 2023-11-02 at 13:07:21 +0100