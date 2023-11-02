---
title: InternetManager
summary: Represents a manager that handles the internet connection and sets up a web server. 

---

# InternetManager



Represents a manager that handles the internet connection and sets up a web server.  [More...](#detailed-description)


`#include <InternetManager.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[InternetManager](/embedded/class_internet_manager/#function-internetmanager)**()<br>Implementation of the [InternetManager](/embedded/class_internet_manager/) class.  |
| void | **[initialize](/embedded/class_internet_manager/#function-initialize)**([Screen](/embedded/class_screen/) * givenScreen, [StateManager](/embedded/class_state_manager/) * givenStateManager)<br>Initialize the Wi-Fi connection and set up the web server.  |
| void | **[listenServer](/embedded/class_internet_manager/#function-listenserver)**()<br>Listen for requests to the server.  |

## Detailed Description

```cpp
class InternetManager;
```

Represents a manager that handles the internet connection and sets up a web server. 

**Author**: F.S. Koulen

The server can be used to control the LCD backlight and to get the current measurement. The screen is used to display messages. The state manager is used to post the current measurement.


License: GNU GPLv3 

## Public Functions Documentation

### function InternetManager

```cpp
InternetManager()
```

Implementation of the [InternetManager](/embedded/class_internet_manager/) class. 

**Author**: F.S. Koulen

Has methods to handle the internet connection, to set up a web server, and to handle requests. The server can be used to control the LCD backlight and to get the current measurement.


License: GNU GPLv3 

 Constructor of the [InternetManager](/embedded/class_internet_manager/) class. Initializes the JSON buffer and the server. 


### function initialize

```cpp
void initialize(
    Screen * givenScreen,
    StateManager * givenStateManager
)
```

Initialize the Wi-Fi connection and set up the web server. 

**Parameters**: 

  * **givenScreen** The screen to use for displaying messages. 
  * **givenStateManager** The state manager to use for posting the current measurement. 


### function listenServer

```cpp
void listenServer()
```

Listen for requests to the server. 

This method should be called in the loop. 


-------------------------------

Updated on 2023-11-02 at 13:07:21 +0100