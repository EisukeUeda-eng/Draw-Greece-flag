・How to generate images of each flag

Include mypnm.c and mypnm.h respectively in addition to the main function ("country name".c) that draws each flag.


(1) How to create an image of the Greek flag (Greece.c)

First, divide the vertical length (HEIGHT) into 9 equal parts and create a blue and white striped pattern by painting each step from 0 to the maximum (WIDTH) with blue for odd numbered steps counting from the top and white for even numbered steps.

Next, draw a blue square in the upper left corner with one side as long as five steps.

Finally, complete by drawing a white cross inside that blue square.



