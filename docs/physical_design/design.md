---
title: Design
---

# Design

# Concept

Work out your idea of the physical product

- [ ]  The user and the user needs are described
- [ ]  The main goals of the product is described
- [ ]  The requirements (SMART) for the product are given
- [ ]  It is clear how the shape, dimensions and behaviour of the physical product reaches the goal and requirements
- [ ]  The desired physical product and the interaction with the product is demonstrated with visualisations (sketches
  are sufficient)

[Product Thinking - A Comprehensive Guide to Product Design Process with a Product Thinking Mindset | by Sudarshan Sahu | UX Planet](https://uxplanet.org/product-thinking-a-comprehensive-guide-to-product-design-process-with-a-product-thinking-mindset-7cfaa6a569d7)

## User

- Working adult
- Has multiple appointments
- Loses track of time easily
- Is often late & has to hurry

## User Needs

- Way to keep track of what time and day it is
- A quick way to see what appointments are coming up

## Goals

- Show the time and date (so that user knows what time and date it currently is)
- Show calendar appointments (so that user has an insight in their day)
- Make a sound every hour (to indicate that an hour has passed)
- Show bird every hour (to make the device more interactive and fun to look at)

## Requirements

### Physical Design

- Has a case which hides the embedded devices
- Has an item that represents the bird of the cuckoo clock. I've decided to go with a Pac-Man themed design, so the bird
  will be Pac-Man.

Inspiration for case:

- [Modern cuckoo clocks](https://www.home-designing.com/unique-modern-style-cuckoo-wall-clocks-for-sale)

<figure class="inline start" markdown>
![Modern Cuckoo Black](https://i0.wp.com/www.thelindentreedecor.co.uk/wp-content/uploads/2022/05/F6D89CD7-9718-42D1-A55B-4D6E639A79F3.jpeg?fit=777%2C573&ssl=1){ width="600" }
  <figcaption>Modern Cuckoo Clock</figcaption>
</figure>
<figure markdown>
![Pac-Man](https://www.posters.nl/media/catalog/product/cache/cb3faf85ecb1e071fdba48f981c86454/p/a/pac-man-maze-poster-61x91.5cm.jpg){ width="300" }
  <figcaption>Pac-Man</figcaption>
</figure>

### Embedded Devices

- Has a temperature and humidity sensor that measures the temperature and humidity
- Has an RTC module that keeps track of the time
- Has an LCD that shows the current date & time, upcoming appointments and current temperature
- Has a button to switch the content of the LCD (current date & time / upcoming appointments / current temperature)
- Has a servo motor that moves the Pac-Man
- Has a button to show the Pac-Man & make a sound
- Has a buzzer that makes a sound every hour
- Uses WEMOS to do the following:
    - Uses the WI-FI manager for configuration of SSID, User ID (UID) en Password (PWD) for connecting to the network.
    - Send measured temperature and humidity data to the application backend over http(s)
    - Retrieves appointments from the application backend over http(s)

### Web Application

- Has interface to manage appointments
- Has database which stores appointments
- Has REST API to communicate with database

## Shape, Dimensions & Behaviour

Over here I have created a little sketch of what the physical product will look like. The shape of the product is a box
where the front is inspired by the game Pac-Man. The dimensions of the product are not yet known, but it will be a small
box that can be placed on a desk or a shelf, or hang on a well. The product will be made out of plexiglas. The Pac-Man
layout will be engraved on the front of the box. The embedded devices will be placed inside the box. The Pac-Man will
represent the bird of the cuckoo clock and will be 3D printed using yellow and black PLA. The button tops that represent
the ghost of the game will be 3D printed in PLA as well. The behaviour of the product is that it shows the time and
date, upcoming appointments and the current temperature. It
also makes a sound every hour and shows a bird.

![Sketch](https://res.cloudinary.com/dr6r2hv4m/image/upload/v1695039160/hva/iot/sketch_jnana2.png)
[Link to image](https://res.cloudinary.com/dr6r2hv4m/image/upload/v1695039160/hva/iot/sketch_jnana2.png)

# Digital Manufacturing & Material

Choice the material and manufacturing method you want to use

- [ ]  The chosen device is described
- [ ]  The chosen material is described
- [ ]  The choice for the digital manufacturing technique(s) and material(s) is justified.  
  (Describe what properties of the material fit your concept best. For example: Think about the strength, or speed of
  creating with the device and the chosen material)

## Device

To create the physical product I will use the following devices:

- BRM 6090 Laser Machine
  This machine can be found in the Makers Lab. This device will be used to create the front plate of the product.
  The game layout will be engraved on the plate. The holes for the LCD, buttons and buzzer will be cut out of the plate.
- Ultimaker 2+ Connect 3D Printer
  This machine can be found in the Makers Lab as well. This device will be used to create the Pac-Man and the ghost
  button tops.
- [3D printer](https://www.fablabamersfoort.nl/machines/3d-printer/)

## Material
**Case**  
The case will be made out of plexiglas. The plexiglas will be black and the game layout will be engraved on the
plate. The holes for the LCD, buttons and buzzer will be cut out of the plate. I have chosen for plexiglas because the 
color of the plexiglas will fit the theme of the product. The plexiglas is also easy to cut and engrave with the laser,
but strong enough to be a case for my product.

**Pac-Man and Ghosts**  
The Pac-Man and Ghosts will be 3D printed. I have chosen for PLA because it is easy to print with, and it is strong
enough to be used as a button top. I have chosen for yellow and black PLA because it fits the theme of the product.
For the ghosts I have not yet chosen the color of PLA. I will probably go with the colors of the ghosts in the game.

# Digital Design
Create your digital design for your chosen manufacturing technique and material using appropriate software

- [ ]  Choices for software are given
- [ ]  Design process is documented
- [ ]  Visuals of the software and different stages of the design are presented
- [ ]  Design files consist of the different versions that were created and that are described in your documentation.