// Assignment 1 Mandelbrot: Mandelbrot generation functions
// mandelbrot.c
//
// Completed by
//  ... JOVANNI TJUANDI (Z5213864)
//
// Modified on 2018-September-05
// Angus - Connor (WED - KORA)
//
// Version 1.0.2: Fix minor typos in comments.
// Version 1.0.1: Fix issues with spacing and indentation.
// Version 1.0.0: Assignment released.

#include <stdio.h>
#include "mandelbrot.h"
#include "pixelColor.h"

// Add your own function prototypes here
static struct complex new_w (struct complex w, struct complex c);
static double SquareLength (struct complex w);
static double distance (int power);

// Take a pixel grid and and the path from the web browser used to
// request the 'tile'.
//
// The requestPath will be in the form "/mandelbrot/2/{zoom}/{x}/{y}.bmp".
// In the query, 'x' and 'y' are decimals and describe the 'center' of the
// tile and need to be converted into a complex number.
// 'zoom' is an integer representing the zoom level for the tile.
void serveMandelbrot(
    struct pixel pixels[TILE_SIZE][TILE_SIZE],
    char *requestPath
) {
    struct complex center = {0.0, 0.0};
    int z = 7;

    sscanf(
        requestPath,
        "/mandelbrot/2/%d/%lf/%lf.bmp",
        &z, &center.re, &center.im
    );

    // Use drawMandelbrot to draw the image.
    drawMandelbrot(pixels, center, z);
}

// Draw a single Mandelbrot tile, by calculating and colouring each of
// the pixels in the tile.
//
// Your function "returns" this tile by filling in the `pixels` 2D array
// that is passed in to your function.
//
// The `pixels` array is TILE_SIZE high and TILE_SIZE wide.
// The bottom left corner of the image is pixels[0][0].
//
// `center` is a complex number, representing the center of the tile.
// `z` is used to calculate the distance between each pixel in the image.
// Each pixel is 2^(-z) apart from each other.
void drawMandelbrot(
    struct pixel pixels[TILE_SIZE][TILE_SIZE],
    struct complex center,
    int z
) {
    int row = 0;
    int col = 0;
    double dist = distance(z);
    
    struct complex corner;
    corner.re = center.re - ((TILE_SIZE/2)*(dist));
    corner.im = center.im - ((TILE_SIZE/2)*(dist));
    
    while (row < TILE_SIZE) {
        col = 0;
        while (col < TILE_SIZE) {
            struct complex position = corner;

            position.re = position.re + col * dist;
            position.im = position.im + row * dist;
            
            pixels [row][col] = pixelColor(escapeSteps(position));
            col = col + 1;
        }
        row = row + 1;
    }  
}



// Determine the number of steps required to escape the Mandelbrot set,
// for the given complex number `c`.
int escapeSteps(struct complex c) {
    int steps = 0;
    struct complex w;
    w.re = 0.0;
    w.im = 0.0;

    while (SquareLength(w) < 4 && steps < MAX_STEPS) {
        w = new_w (w,c);
        steps = steps + 1;
    }
    if(steps == MAX_STEPS){
         steps = NO_ESCAPE;
    }
    
    return steps;
}

// new_w squares w and adds c to it
static struct complex new_w (struct complex w, struct complex c) { 
    struct complex new_w;
    new_w.re = w.re*w.re - w.im*w.im + c.re;
    new_w.im = 2 * w.re * w.im + c.im;

    return new_w;
}

// SquareLength returns the square of length of a complex number
static double SquareLength (struct complex w) {
    double squarelength = w.re*w.re + w.im*w.im;
    return squarelength;
}

// distance is the distance between each pixel which is (2^(zoom))
static double distance (int power) {
   int count = 0;
   double distance = 1.0;
   while (count < power) {
      distance = distance*(0.5);
      count = count + 1;
   }
   return distance;
}
