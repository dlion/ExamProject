ExamProject
===========

This is my Exam Project for my high school gradutation.

During the year I wrote some sources in C using OpenCV.

I wrote 5 programs and 1 library for this.


## Calibra

It's a program that allow to find and track the colour that you want, mixing HSV values.

When you find the colour you can save this in a configuration file pressing 's' also if you press 'q' the program ends.

When you save the values in the configuration file this allow to find this color also with other programs.


## Bubbles

It's a little game wrote in C, use thread, opencv functions and other things.

You have to touch with your "color" the red balls on the screen; if you touch the blue ball you lose.

First of all, you have to run the Calibra program to bring HSV values to find your color.


## Draw

With this program you can color on the screen.

In this screen you can find 3 rectangle, one with blue, one with red, one with green color.

If you touch one of this you can color with it.

If you press 'c' you delete all and reset the "paintbrush".

First of all, you have to run the Calibra program to bring HSV values to find your color.


## Head

This program tracks your head on the screen, this program uses the cascade files to recognize your face and if you want also the eyes.


## Movement

If you want to monitor a place, with this program you can.

This program saves a frame it has suffered a modify respecting the origin; at the end of the program this saves all frames how video file (avi) so you can watch
only frames that interesting you.


## Lib

This library contain some functions to run other programs.

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


```
make
```
or

```
g++ `pkg-config --cflags --libs opencv` -pthread <source> -o <binary>
```


## About

**I took 30 points for this project on my exam.**

If you want to read my relaction with Images you can see *Relazione.pdf* but it is in **italian language**.

Author: Domenico *Leone* Luciani

Email: domenicoleoneluciani[AT]gmail[DOT]com

Site: http://dlion.it

#### Status: Complete
