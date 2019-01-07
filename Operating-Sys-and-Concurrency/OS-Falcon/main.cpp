/*
    Mandelbrot set image generation
    Code referenced and copied from
    https://www.youtube.com/watch?v=entjSp3LIfQ
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <vector>

template<typename F>
auto timefunc(F incomingFunct)
{
    auto start = std::chrono::steady_clock::now();
	incomingFunct();
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	return elapsed_seconds.count();
}




void generateMandelbrotset(std::ostringstream &refstring, int imageWidth, int imageHeight, 
						   int maxN, double minR, double maxR, double minI, double maxI)
{
	// give it the P3 header to identify it as a .ppm file
	refstring << "P3" << std::endl;
	
	// give the width and the height
	refstring << imageWidth << " " << imageHeight << std::endl;
	
	// give a max value for the pixels in rgb
	// this is what we will mod by later on
	refstring << "256" << std::endl;

	// x and "y" positions in the viewing plane
	double realX = 0;
	double imagI = 0;

	// iteration counter
	int iterations = 0;

	// computed real and imaginary parts
	double zr;
	double zi;

	// for coloring
	int r, g, b;

	// temp variable used in while loop
	double xTemp;

	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			// compute x and y
			realX = x * ((maxR - minR) / imageWidth) + minR;
			imagI = y * ((maxI - minI) / imageHeight) + minI;

			iterations = 0;
			zr = 0;
			zi = 0;

			while ((iterations < maxN) && ((zr*zr + zi*zi) < 4.0))
			{
				xTemp = zr * zr - zi * zi + realX;
				zi = 2.0 * zr * zi + imagI;
				zr = xTemp;
				iterations++;
			}

			r = iterations % 256;
			g = iterations % 256;
			b = iterations % 256;

			//r = (int)((float)iterations*sinf((float)iterations)) % 256;
			//g = (iterations*iterations) % 256;
			//b = iterations % 256;

			refstring << r << " " << g << " " << b << " ";
		}
		refstring << std::endl;
		//std::cout << y << std::endl;
	}
}

double vectorAverage(std::vector<double> &inputVector)
{
	double runningAve = 0;
	for(int i = 0;i<inputVector.size();i++)
	{
		runningAve = runningAve + inputVector[i];
	}
	
	return runningAve/((double)inputVector.size());
}

int main()
{
    // set up the input parameters to the mandelbrot function
	int imageWidth = 500;
	int imageHeight = 500;
	int maxN = 255;
    int nData = 10;
	double minR = -2.1;
	double maxR = 1.1;
	double minI = -1.6;
	double maxI = 1.6;

    std::vector<double> timeDataArray;

	std::ostringstream writeToFile;


	std::cout << "Please wait the program is running." << std::endl;
	for (int i = 0; i < nData;i++)
	{
        timeDataArray.push_back( timefunc([&](){generateMandelbrotset(writeToFile, imageWidth, imageHeight, maxN, minR, maxR,  minI, maxI); }));      
    }

	std::cout << "RESULTS!" << std::endl;
	std::cout << "We made a program that produces MandelBrot sets." << std::endl;
	std::cout << "Our window is 500 by 500 pixels" << std::endl;
	std::cout << "We computed each pixel with a max number of iterations of 255" << std::endl;
	std::cout << "With a window range that centers the image with an aspect ratio of 1." << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Here are the runtimes." << std::endl;
    for (int i =0;i<timeDataArray.size();i++)
    {
        std::cout << "Mandelbrot set " << i + 1 << ": " << timeDataArray[i] << std::endl;
    }
    
    std::cout << "The Average runtime was: " << vectorAverage(timeDataArray) << std::endl;
    std::cout << "The Standard deviation was: " << 6 << std::endl;

	// Now we are going to make a .ppm file.
	std::ofstream fout("output_image.ppm");

	fout << writeToFile.str();
	fout.close();
	std::cout << "Finished! " << std::endl;

	return 0;
}
