ExamProject
===========

This is my Exam Project for my high school gradutation.

During the year I wrote some sources in C using OpenCV.

I wrote 5 program and 1 library for this.


## Calibra

Is a program that allow to find and track the colour that you want, mixing HSV values.

When you find the colour you can save this in a configuration file pressing 's' also if you press 'q' the program ends.

When you save the values in the configuration file this allow to find this color also with other programs.


## Bubbles

Is a little game wrote in C, use thread, opencv functions and other things.

With your "color" you have to touch the red balls on the screen; if you touch the blue ball you lose.

First of all, you have to run the Calibra program for bring HSV values for find your color.


## Draw

With this program you can color on the screen.

In this screen you can find 3 rectangle, one with blue, one with red, one with green color.

If you touch one of this you can color with it.

If you press 'c' you delete all and reset the "paintbrush".

First of all, you have to run the Calibra program for bring HSV values for find your color.


## Head

This program track your head on the screen, this program use the cascade files for recognize your face and if you want also the eyes.


## Movement

If you want monitoring a place, with this program you can.

This program save a frame it has suffered a modify respecting the origin; at the end of the program this save all frame how video file (avi) so you can watch
only frame that interesting you.


## Lib

This library containing some functions for run other programs.

## License

ExamProject is released under the GNU General Public License (GPL3):

Copyright (C) 2012 Domenico Luciani domenico.luciani@email.it

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

On Debian systems, the complete text of the GNU General Public License can be found in /usr/share/common-licenses/GPL-3.

You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/.


## Dependencies

* OpenCV
* g++
* ffmpeg


## How to build


`make`


## About

I taken 30 point for this project on my exam. (the maximum)
