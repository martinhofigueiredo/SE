---
title:  'Game Player with Wifi controlller'
shorttitle: 'Esp 32 Game Console'
author:
- author: Martinho Figueiredo
  email: up201506179@fe.up.pt
- author: Túlio Soares
  email: upup201800165@fe.up.pt
institute: Faculdade de Engenharia, Universidade do Porto
keyword:
  - ESP32
  - RTOS
lineno: false
abbreviation:
  - RTOS, real time operationg system
abstract: |
  In this project we will create and evaluate a small game controller and display based on a ESP32 Microcontroller
bibliography: references.bib
template: scientific_reports
documentclass_options: 
  - final
...

# Introduction
 The system we developed is intend to be used as a small digital clock with a few minigames. This serves as an example of a IoT device capable of displaying some up to date information like the weather and having some interative features that need a realtime response as for the minigames.


# Methods

We tried to structure the code for the functions we wanted to develop in a "apps" a  class object that has a `setup` method that handles all the configuration of the microcontroller and a `routine` method that has to be iterated on to update the app.

To choose which app is running we added a button to cycle trough a app list and change which app is running at a time. There is never more than one app running at one time.

The timing of each function was done using the `micro()` to timestamp the begin and end of the function and the value presented here was calculated as the last result of a rolling average after 10000 cycles.

The memory usage of our programs takes into account the assets needed to run the applications and the binary that compiled and uploaded  

# Apps

## Weather

![Weather Screen](pic/weather.jpg)
 
- This app 

## Clock

![Clock Screen](pic/clock.jpg)

# Games

## Alien Attack
- This game uses two buttons to move a spaceship side ways on the screen in order to hit enemys.
![Alien Attack Load Screen](pic/alienattack.jpg)
![Alien Attack Game Screen](pic/alienattack_play.jpg)

## Bounce Ball
- This game uses two buttons to move platform side ways on the screen in order to catch and return the ball to break the block on the top of the screen.
![Bounce Ball Load Screen](pic/bounceball.jpg)
![Bounce Ball Game Screen](pic/bounceball_play.jpg)


## Results
<!--
| App             | Flash (MAX 1310720 bytes) | RAM (MAX 327680 bytes) | Run Time (Avg) |
|:---------------:|:-------------------------:|:----------------------:|:--------------:|
| Clock & Weather | 1274853 bytes (97.3%)     | 43488 bytes (13.3%)    |                |
| SmartClock      | 909273 bytes (69.4%)      | 39836 bytes (12.2%)    | $1.68 \mu s$   |
| Weather         | 1235733 bytes (94.3%)     | 42284 bytes (12.9%)    | $10091 \mu s$  |
| Both Games      | 942589 bytes (71.9%)      | 17676 bytes (5.4%)     |                |
| Alien Attack    | 874065 bytes (66.7%)      | 17396 bytes (5.3%)     | $12453 \mu s$  |
| Bounce Ball     | 364077 bytes (27.8%)      | 17164 bytes (5.2%)     | $873 \mu s$    |
-->


Footnotes can be entered using this code.


Figures are included like this.

<!--![This is gonna be the caption.](pics/dummy.pdf){#fig:dummy width=40% height=20%}

And referenced from here as Fig. @fig:dummy.
-->
Complex tables can use standard LaTeX code as this one.

<!---
Table in LaTeX format because of fancy formatting
-->

# Discussion



# References