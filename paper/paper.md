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

In this paper, we explore the differences between Arduino and FreeRTOS implementations for embedded systems. Arduino is an open-source electronics platform that is based on simple software and hardware. It is often used for prototyping and hobby projects, and it features a simplified programming environment and a large community of users. On the other hand, FreeRTOS is a real-time operating system (RTOS) that is designed for use in embedded systems. It is a small, lightweight, and customizable operating system that is designed to be easy to use and understand. The key differences between the two lie in the level of control and flexibility offered by each platform. Arduino is best suited for simple, single-threaded projects, while FreeRTOS is more suitable for larger, multi-threaded projects that require real-time performance. Overall, both Arduino and FreeRTOS have their own advantages and disadvantages and the choice of which to use will depend on the specific requirements of the project.

 The system we developed is intend to be used as a small digital clock with a few minigames. This serves as an example of a IoT device capable of displaying some up to date information like the weather.

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