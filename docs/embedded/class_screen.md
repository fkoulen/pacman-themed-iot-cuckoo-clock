---
title: Screen
summary: Represents the screen of the device. 

---

# Screen



Represents the screen of the device.  [More...](#detailed-description)


`#include <Screen.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[Screen](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_screen/#function-screen)**()<br>Implementation of the [Screen](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_screen/) class.  |
| void | **[initializeLCD](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_screen/#function-initializelcd)**()<br>Initialize the LCD and turn on the backlight.  |
| void | **[printCustomCharacter](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_screen/#function-printcustomcharacter)**(int position, int row, int character)<br>Print a custom character on the given location and row.  |
| void | **[printText](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_screen/#function-printtext)**(const String & line, unsigned int positionLine, unsigned int row)<br>Print the given text on the given line and row.  |
| void | **[printText](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_screen/#function-printtext)**(const String & firstLine, unsigned int positionFirstLine, const String & secondLine, unsigned int positionSecondLine, bool clear)<br>Clear the LCD if specified and show the given text on the first and second line.  |
| void | **[printText](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_screen/#function-printtext)**(const String & firstLine, const String & secondLine)<br>Clear the LCD and show the given text on the first and second line.  |
| void | **[createCustomCharacter](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_screen/#function-createcustomcharacter)**(int location, byte pixels[])<br>Create a custom character on the given location with the character pixels.  |
| void | **[clear](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_screen/#function-clear)**()<br>Clear the LCD.  |
| bool | **[toggleBacklight](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_screen/#function-togglebacklight)**()<br>Toggle the backlight.  |
| bool | **[isBacklightOn](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_screen/#function-isbacklighton)**() const<br>Check whether the backlight is on.  |

## Detailed Description

```cpp
class Screen;
```

Represents the screen of the device. 

**Author**: F.S. Koulen

This class is responsible for printing text on the screen and creating custom characters.


License: GNU GPLv3 

## Public Functions Documentation

### function Screen

```cpp
Screen()
```

Implementation of the [Screen](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_screen/) class. 

**Author**: F.S. Koulen

This class is used to control the LCD. It contains methods to initialize the LCD and to print text on the LCD.


License: GNU GPLv3 

 Constructor for the [Screen](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_screen/) class. This constructor is empty because the LCD is initialized in the `initializeLCD` method. 


### function initializeLCD

```cpp
void initializeLCD()
```

Initialize the LCD and turn on the backlight. 

### function printCustomCharacter

```cpp
void printCustomCharacter(
    int position,
    int row,
    int character
)
```

Print a custom character on the given location and row. 

**Parameters**: 

  * **position** The position for the character 
  * **row** The row for the character 
  * **character** The character to print 


### function printText

```cpp
void printText(
    const String & line,
    unsigned int positionLine,
    unsigned int row
)
```

Print the given text on the given line and row. 

**Parameters**: 

  * **line** The text to print 
  * **positionLine** The position for the text 
  * **row** The row for the text 
  * **clear** Whether to clear the LCD before printing the text 


### function printText

```cpp
void printText(
    const String & firstLine,
    unsigned int positionFirstLine,
    const String & secondLine,
    unsigned int positionSecondLine,
    bool clear
)
```

Clear the LCD if specified and show the given text on the first and second line. 

**Parameters**: 

  * **clear** Whether to clear the LCD before printing the text 
  * **firstLine** The text for the first line 
  * **positionFirstLine** The position for the first line 
  * **secondLine** The text for the second line 
  * **positionSecondLine** The position for the second line 


### function printText

```cpp
void printText(
    const String & firstLine,
    const String & secondLine
)
```

Clear the LCD and show the given text on the first and second line. 

**Parameters**: 

  * **firstLine** The text for the first line 
  * **secondLine** The text for the second line 


### function createCustomCharacter

```cpp
void createCustomCharacter(
    int location,
    byte pixels[]
)
```

Create a custom character on the given location with the character pixels. 

**Parameters**: 

  * **location** The location of the custom character 
  * **pixels** The character's pixels 


### function clear

```cpp
void clear()
```

Clear the LCD. 

### function toggleBacklight

```cpp
bool toggleBacklight()
```

Toggle the backlight. 

**Return**: Whether the backlight is now on or off 

### function isBacklightOn

```cpp
bool isBacklightOn() const
```

Check whether the backlight is on. 

**Return**: Whether the backlight is on 

-------------------------------

Updated on 2023-11-02 at 14:37:01 +0100