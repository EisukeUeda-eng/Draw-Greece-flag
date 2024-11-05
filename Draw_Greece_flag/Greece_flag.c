#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mypnm.h"

#define WIDTH 640
#define HEIGHT 480
#if 1
int main()
{
    int i, x, y;
    unsigned char *red, *grn, *blu;

    // Allocate memory for color channels
    red = (unsigned char *)malloc(sizeof(char) * WIDTH * HEIGHT);
    grn = (unsigned char *)malloc(sizeof(char) * WIDTH * HEIGHT);
    blu = (unsigned char *)malloc(sizeof(char) * WIDTH * HEIGHT);

    // Create alternating blue and white stripes
    for (i = 0; i < 9; i++) {
        // Even-numbered stripes are blue
        if (i % 2 == 0) {
            for (y = (HEIGHT / 9) * i; y < (HEIGHT / 9) * (i + 1); y++) {
                for (x = 0; x < WIDTH; x++) {
                    red[y * WIDTH + x] = 13;
                    grn[y * WIDTH + x] = 94;
                    blu[y * WIDTH + x] = 175;
                }
            }
        }
        // Odd-numbered stripes are white
        else {
            for (y = (HEIGHT / 9) * i; y < (HEIGHT / 9) * (i + 1); y++) {
                for (x = 0; x < WIDTH; x++) {
                    red[y * WIDTH + x] = 255;
                    grn[y * WIDTH + x] = 255;
                    blu[y * WIDTH + x] = 255;
                }
            }
        }
    }

    // Create the blue square in the upper left
    for (y = 0; y < HEIGHT / 9 * 5; y++) {
        for (x = 0; x < HEIGHT / 9 * 5; x++) {
            red[y * WIDTH + x] = 13;
            grn[y * WIDTH + x] = 94;
            blu[y * WIDTH + x] = 175;
        }
    }

    // Create the horizontal part of the white cross
    for (y = HEIGHT / 9 * 2; y < HEIGHT / 9 * 3; y++) {
        for (x = 0; x < HEIGHT / 9 * 5; x++) {
            red[y * WIDTH + x] = 255;
            grn[y * WIDTH + x] = 255;
            blu[y * WIDTH + x] = 255;
        }
    }

    // Create the vertical part of the white cross
    for (x = HEIGHT / 9 * 2; x != (HEIGHT / 9 * 2) + (HEIGHT / 9); x++) {
        for (y = 0; y < HEIGHT / 9 * 5; y++) {
            red[y * WIDTH + x] = 255;
            grn[y * WIDTH + x] = 255;
            blu[y * WIDTH + x] = 255;
        }
    }

    // Save the image
    save_ppm("Greece.ppm", red, grn, blu, WIDTH, HEIGHT);

    // Free allocated memory
    free(red);
    free(grn);
    free(blu);

    return 0;
}
#endif
