// Assignment 1 Mandelbrot: Mandelbrot generation functions
// mandelbrot.c
//
// Completed by
//  ... (z0000000)
//
// Modified on 2018-??-??
// Tutor's name (dayHH-lab)
//
// Version 1.0.2: Fix minor typos in comments.
// Version 1.0.1: Fix issues with spacing and indentation.
// Version 1.0.0: Assignment released.

#include <stdio.h>
#include <math.h>

// Add your own #includes here

#include "mandelbrot.h"
#include "pixelColor.h"

// Add your own #defines here

// Add your own function prototypes here
static struct complex new_w (struct complex w, struct complex c);
static double absoluteValue (struct complex w);

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
    double dist = pow (2, -z);
    int steps;
    
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

    while (absoluteValue(w) < 2 && steps < MAX_STEPS) {
        w = new_w (w,c);
        steps = steps + 1;
    }
    if(steps == MAX_STEPS - 1){
         steps = NO_ESCAPE;
    }
    
    return steps;
}

// Add your own functions here.
static struct complex new_w (struct complex d, struct complex c) {
    struct complex p;
    p.re = d.re*d.re - d.im*d.im + c.re;
    p.im = 2 * d.re * d.im + c.im;

    return p;
}
static double absoluteValue (struct complex k) {
    double absolute = (sqrt(pow(k.re , 2) + pow(k.im , 2)));
    return absolute;
}
// Remember to make them static.
