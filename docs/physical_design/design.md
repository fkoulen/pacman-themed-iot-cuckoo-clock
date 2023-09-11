---
title: Design
---
# Design

# **Concept**

Work out your idea of the physical product

- [ ]  The user and the user needs are described
- [ ]  The main goals of the product is described
- [ ]  The requirements (SMART) for the product are given
- [ ]  It is clear how the shape, dimensions and behaviour of the physical product reaches the goal and requirements
- [ ]  The desired physical product and the interaction with the product is demonstrated with visualisations (sketches are sufficient)

[Product Thinking - A Comprehensive Guide to Product Design Process with a Product Thinking Mindset | by Sudarshan Sahu | UX Planet](https://uxplanet.org/product-thinking-a-comprehensive-guide-to-product-design-process-with-a-product-thinking-mindset-7cfaa6a569d7)

# User

- Simple human being
- Has multiple appointments
- Loses track of time easily
- Is often late & has to hurry

# User Needs

- Way to keep track of what time and day it is
- A quick way to see what appointments are coming up

# Goals

- Show the time and date (so that user knows what time and date it currently is)
- Show calendar appointments (so that user has an insight in their day)
- Make a sound every hour (to indicate that an hour has passed)
- Show bird every hour (to make the device more interactive and fun to look at)

# Requirements

## Physical Design

- Has a case which hides the embedded devices
- Has a item that represents the bird of the cuckoo clock

Inspiration for case:
[Modern cuckoo clocks](https://www.home-designing.com/unique-modern-style-cuckoo-wall-clocks-for-sale)
![Modern Cuckoo Black](https://i0.wp.com/www.thelindentreedecor.co.uk/wp-content/uploads/2022/05/F6D89CD7-9718-42D1-A55B-4D6E639A79F3.jpeg?fit=777%2C573&ssl=1)

## Embedded Devices

- Uses WEMOS to do the following:

  - Send measured sensor data to the application backend (the average temperature in a day perhaps) over http(s)
  - Retrieves appointments from the application backend over http(s)
- Has a button to switch the content of the LCD display (go to next time, or even show any other information like the temperature in the room)
- Has a button to show the bird & make a sound
- Has a LCD display that shows appointment, date and time
- Has a buzzer that makes a sound every hour
- The embedded device uses the WIFI manager for configuration of SSID, User ID (UID) en Password (PWD) for connecting to the network.

## Web Application

- Has interface to manage appointments
- Has database which stores appointments
- Has REST API to communicate with database
