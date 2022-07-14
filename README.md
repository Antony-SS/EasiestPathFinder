# EasiestPathFinder
Takes as an input an array of data representing elevations in a given region (must be square or rectangular region).  

The program will generate a grayscale ppm image representing an elevation map of the area.  On top of that image, the program will highlight the path of least change in elevation across the image from left to right found using the greedy algorithm.  

Red lines on the image represent "failed" paths.  See example data for example input and output data.  Could be improved by implementing recursive backtracking.
