/**
 * Code used and referenced from
 * https://www.tankonyvtar.hu/hu/tartalom/tamop412A/2011-0063_23_introduction_mpi/ar01s12.html
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h> 
#include <vector>
#include <time.h>

using namespace std;
const int PIXELS_IN_X = 2048; // Pixels in the x-direction
const int PIXELS_IN_Y = 2048; // Pixels in the y-direction
const int MAX_ITERS = 3000; // max iteration number

// MANDELBROT SCENE COORDS.
const double Y_MIN = -0.135;   
const double Y_MAX = -0.115;
const double X_MIN = -0.79;  
const double X_MAX = -0.77;

// This is the 2-D array of ints for the Mandelbrot method. (Initialized to zero.)
int IMG_ARRAY[PIXELS_IN_X][PIXELS_IN_Y] = {0}; 

// Escape time method for Mandelbrot image generation, given an x and y value, this will return a number of iterations computed
// at that location
int mandelbrot_Iterations(double calcd_xPos,double calcd_yPos) {
	int iters = 0;
	double zx = 0;
	double x_Temp = 0;
	double zy = 0;
	// we iterate until max. iteration count MAX_ITERS, or until z^2 (complex!) runs over 4 - this means, our series will run to infinity, so it's not part of the set
	while( (iters < MAX_ITERS) && (zx * zx + zy * zy) < 4 ) {
		x_Temp = zx*zx - zy*zy + calcd_xPos;
		zy = 2*zx*zy + calcd_yPos;
		zx = x_Temp;
		iters++;
	}
	return iters;
}

int main(int argc, char **argv){
	if(argc < 2) {
		cout << "You should specify an output file." << endl;
		cout<< argv[0] <<" out_file.ppm "<<endl;
		return 1;
	}

	double pixelWidthInX = 0; 
	double pixelWidthInY = 0; 

	// Starting Point
	double calcd_xPos = X_MIN; 
	double calcd_yPos = Y_MIN;

	// Timings...
	time_t timeOne;
	time_t timeTwo; 

	ofstream outputFile;  
	string filename1(argv[1]);
	char *fileName1 = (char*)filename1.c_str();

	//prepare the step resolution
	pixelWidthInX = (X_MAX-X_MIN) / PIXELS_IN_X;
	pixelWidthInY = (Y_MAX-Y_MIN) / PIXELS_IN_Y;

	time(&timeOne);  // we get a time value at this point

	// Calculate the iterations for each pixel.
	for(int i = 0; i < PIXELS_IN_X; i++) {
		calcd_yPos = Y_MIN;  // at every new step in X direction, we start at the first Y value 
		for(int j = 0; j < PIXELS_IN_Y; j++) {
			// Get the iters at this point.
			IMG_ARRAY[i][j] = mandelbrot_Iterations(calcd_xPos, calcd_yPos);
			calcd_yPos = calcd_yPos + pixelWidthInY;
		}
		calcd_xPos = calcd_xPos + pixelWidthInX;
	}
	// we get another time at this point, so we can calculate the elapsed time for the entire procedure.
	time(&timeTwo);

	cout << "Total elapsed time for calculation: " << timeTwo - timeOne << " secs." << endl;

	// file IO
	outputFile.open(fileName1);
	outputFile << "P3\r\n";
	outputFile << PIXELS_IN_X;
	outputFile << " ";
	outputFile << PIXELS_IN_Y;
	outputFile << "\r\n";
	outputFile << "255\r\n";

	for(int i=0;i<PIXELS_IN_X;i++) {
		for(int j=0;j<PIXELS_IN_Y;j++) {
			if( (IMG_ARRAY[i][j] < 256) ) {
				outputFile << IMG_ARRAY[i][j] << " 0 0"; 
			}
			else if( IMG_ARRAY[i][j] < 512) {
				outputFile << "255 " << IMG_ARRAY[i][j]-256 << " 0";
			}
			else if( IMG_ARRAY[i][j] < 768) {
				outputFile << "255 255 " << IMG_ARRAY[i][j]-512;
			}
			else {
				outputFile << "0 0 0 ";
			} 
			outputFile << " ";
		}
		outputFile << "\r\n";
	}

	outputFile.close();  // we close our file

	time(&timeTwo);  // and give another elapsed time info (IO included)

	cout << "Total elapsed time for computation, coloring, and file output: " << timeTwo - timeOne << " secs \r\n";
	return 0;
}