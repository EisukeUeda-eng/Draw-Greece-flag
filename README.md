・How to generate images of each flag

Include mypnm.c and mypnm.h respectively in addition to the main function ("country name".c) that draws each flag.


(1) How to create an image of the Greek flag (Greece.c)

First, divide the vertical length (HEIGHT) into 9 equal parts and create a blue and white striped pattern by painting each step from 0 to the maximum (WIDTH) with blue for odd numbered steps counting from the top and white for even numbered steps.
Next, draw a blue square in the upper left corner with one side as long as five steps.
Finally, complete by drawing a white cross inside that blue square.


(2) How to create an image of the Seychelles flag (Seychelles.c)

First, draw a blue line from (0,479) to (160,0). At this point, the coordinates of the points plotted when drawing the line are recorded in the array.
Next, draw a blue triangle by filling in from each y-coordinate with x-coordinate 0 to the x-coordinate that was recorded.
Similarly, for the yellow, red, white, and green areas, first draw a straight line for each color, and then fill in the area for each color by filling in to the coordinates that were recorded when the line was drawn one line before.
However, if the coordinates are not recorded (left at the initial value of 0), the x-coordinate is filled until it reaches the maximum (WIDTH).
