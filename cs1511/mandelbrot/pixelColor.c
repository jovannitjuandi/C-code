// Assignment 1 Mandelbrot: Pixel coloring functions
// pixelColor.c
//
// Completed by
//  ... JOVANNI (z5213864)
//
// Modified on 2018-September-05
// Angus - Connor (WED - KORA)
//
// Version 1.0.1: Fix issues with spacing and indentation.
// Version 1.0.0: Assignment released.

#include "mandelbrot.h"
#include "pixelColor.h"

// This function should take a number (of steps taken to escape the
// Mandelbrot set), and convert it to a color.
//
// You have artistic licence here, so make your Mandelbrot look amazing.
struct pixel pixelColor(int steps) {
    struct pixel color = {
        .red = steps,
        .green = steps,
        .blue = steps,
    };

    if (steps == NO_ESCAPE) {
      color.red = 255;
      color.green = 255;
      color.blue = 255;
    } else if (steps <= 5) {
      color.red = 250 - (2*steps);
      color.green = 125 + (5*steps);
      color.blue = 150 - (2*steps);
    } else if (steps <= 15) {
      color.red = 240 - 4*(steps - 5);
      color.green = 150 - (steps - 5);
      color.blue = 140 + (10*(steps - 5));
    } else if (steps <= 25) {
      color.red = 3*(steps - 15) + 200;
      color.green = 100 + 8*(steps - 15);
      color.blue = 240 + (steps - 15);
    } else if (steps <= 225) {
      color.red = 230 - steps;
      color.green = 180;
      color.blue = 250;
    } else if (steps <= 255) {
      color.red = 160;
      color.green = 255;
      color.blue = 240;
    } else {
      color.red = 255;
      color.green = 255;
      color.blue = 255;
    }
    return color;
}
