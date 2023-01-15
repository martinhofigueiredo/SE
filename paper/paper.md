---
title:  'Game Player with Wifi controlller'
shorttitle: 'Esp 32 Game Console'
author:
- name: Martinho Figueiredo
  email: up201506179@fe.up.pt
- name: Túlio Soares
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
 The system we developed is intend to be used as a small digital clock with a few minigames. This serves as an example of a IoT device capable of displaying some up to date information like the weather.


![This is gonna be the caption.](pic/bounceball.jpg){#fig:dummy }
<!---
Comments look like this and do not show up in the PDF


References are cited as @mittner2014brain or [@mittner2014brain].
-->

# Methods

We tried to structure the code for the functions we wanted to develop in a "apps" a  class object that has a `setup` method that handles all the configuration of the microcontroller and a `routine` method that is the iterated on to update the app.

These were then placed on freeRTOS task scheduler which was controlled firstly in a round-robin to make sure every task was sucesseful run at least once so we could time it

To get the timing results of each task we used the freeRTOS timing API to return the value of 

Footnotes can be entered using this code[^1].

[^1]: a footnote

Figures are included like this.

<!--![This is gonna be the caption.](pics/dummy.pdf){#fig:dummy width=40% height=20%}

And referenced from here as Fig. @fig:dummy.
-->
Complex tables can use standard LaTeX code as this one.

<!---
Table in LaTeX format because of fancy formatting
-->

# Results

Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor 

# Discussion

Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor 
# References