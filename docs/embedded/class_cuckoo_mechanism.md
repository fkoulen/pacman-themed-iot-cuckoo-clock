---
title: CuckooMechanism
summary: Represents a mechanism for controlling a cuckoo clock. 

---

# CuckooMechanism



Represents a mechanism for controlling a cuckoo clock.  [More...](#detailed-description)


`#include <CuckooMechanism.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[CuckooMechanism](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_cuckoo_mechanism/#function-cuckoomechanism)**()<br>Implementation of the cuckoo mechanism.  |
| void | **[initialize](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_cuckoo_mechanism/#function-initialize)**([Screen](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_screen/) * givenScreen)<br>Initialize the cuckoo mechanism by attaching the servo motor and moving it to the starting position.  |
| void | **[executeCuckooMechanism](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_cuckoo_mechanism/#function-executecuckoomechanism)**(RtcDateTime time)<br>Execute the cuckoo mechanism by displaying the cuckoo state, moving the cuckoo forward, playing the melody and moving the cuckoo backward.  |

## Detailed Description

```cpp
class CuckooMechanism;
```

Represents a mechanism for controlling a cuckoo clock. 

**See**: [https://github.com/robsoncouto/arduino-songs/blob/master/pacman/pacman.ino](https://github.com/robsoncouto/arduino-songs/blob/master/pacman/pacman.ino)

**Author**: 

  * F.S. Koulen 
  * Robson Couto 


This class provides methods for moving the cuckoo forward and backward, playing the melody and displaying the cuckoo state on the screen.


License: GNU GPLv3 

## Public Functions Documentation

### function CuckooMechanism

```cpp
CuckooMechanism()
```

Implementation of the cuckoo mechanism. 

**Author**: F.S. Koulen

Contains methods to play the melody, move the cuckoo and display the cuckoo state.


License: GNU GPLv3 

 Create an instance of the [CuckooMechanism](/2023-2024-semester-1/individual-project/iot-koulenf/embedded/class_cuckoo_mechanism/) class. 


### function initialize

```cpp
void initialize(
    Screen * givenScreen
)
```

Initialize the cuckoo mechanism by attaching the servo motor and moving it to the starting position. 

**Parameters**: 

  * **givenScreen** The screen to use for displaying the cuckoo state 


It also sets the screen to use for displaying the cuckoo state and creates the custom characters.


### function executeCuckooMechanism

```cpp
void executeCuckooMechanism(
    RtcDateTime time
)
```

Execute the cuckoo mechanism by displaying the cuckoo state, moving the cuckoo forward, playing the melody and moving the cuckoo backward. 

**Parameters**: 

  * **time** The current time to display on the screen and to check if the night mode is active. The melody is not played when the night mode is active. 


-------------------------------

Updated on 2023-11-02 at 14:37:01 +0100