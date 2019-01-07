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
#include <cmath>
#include <algorithm>
#include <numeric>


// This method takes an  incoming fucntion and will return the 
// time needed to run that program.
template<typename F>
auto timefunc(F incomingFunct)
{
    auto start = std::chrono::steady_clock::now();
	incomingFunct();
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	return elapsed_seconds.count();
}



// Given the inputs this method will write to a pre-existing string 
// The format needed by a ppm file to make a Mandelbrot image.
auto generateMandelbrotset(std::ostringstream &refstring, int imageWidth, int imageHeight, 
						   int maxN, double minR, double maxR, double minI, double maxI)
{
	// Set-up the header to the .ppm file
	refstring << "P3" << std::endl;
	refstring << imageWidth << " " << imageHeight << std::endl;
	refstring << "256" << std::endl;

	// x and "y" positions in the viewing plane
	auto realX = 0.0;
	auto imagI = 0.0;

	// iteration counter
	auto iterations = 0;

	// computed real and imaginary parts
	auto zr = 0.0;
	auto zi = 0.0;

	// for coloring
	auto r = 0;
	auto g = 0;
	auto b = 0;

	// temp variable used in while loop
	auto xTemp = 0.0;

	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			// linearly interpolate x and y
			realX = x * ((maxR - minR) / imageWidth) + minR;
			imagI = y * ((maxI - minI) / imageHeight) + minI;

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
	}
}

// Given a pre-existing vector of doubles this method will return the 
// average of that set of values
auto vectorAverage(std::vector<double> &inputVector)
{
	auto runningAve = std::accumulate(inputVector.begin(),inputVector.end(),0.0);
	return runningAve/((double)inputVector.size());
}

// Given a pre-existing vector of doubles this method will return the 
// standard Deviation of that set of values.
auto vectorStandardDev(std::vector<double> &inputVector)
{
	// first compute the average
	auto average = vectorAverage(inputVector);
	
	// now we need to sum each (piece - average)^2
	auto runningSum = 0.0;
	for(auto i = 0u;i<inputVector.size();i++)
	{
		runningSum = runningSum + ((inputVector[i] - average)*(inputVector[i] - average));
	}
	runningSum = runningSum/((double)inputVector.size());
	return sqrt(runningSum);
}




int main()
{
    // set up the input parameters to the mandelbrot function
	auto imageWidth = 500;
	auto imageHeight = 500;
	auto maxN = 255;
    auto nData = 10;
	auto minR = -2.1;
	auto maxR = 1.1;
	auto minI = -1.6;
	auto maxI = 1.6;

	// vector to hold times for the various runtimes.
    std::vector<double> timeDataArray;

	// string to hold the "virtual" file until it is ready to be written.
	std::ostringstream writeToFile;

	// time the function a number of times
	std::cout << "Please wait the program is running." << std::endl;
	for (auto i = 0; i < nData;i++)
	{
        timeDataArray.push_back( timefunc([&](){generateMandelbrotset(writeToFile, imageWidth, imageHeight, maxN, minR, maxR,  minI, maxI); }));      
    }

	// output the results.
	std::cout << "RESULTS!" << std::endl;
	std::cout << "We made a program that produces MandelBrot sets." << std::endl;
	std::cout << "We ran our program " << timeDataArray.size() << " times." << std::endl;
	std::cout << "But we only wrote to a file a single time." << std::endl;
	std::cout << "And the writing of the file was not taken into account in " << std::endl;
	std::cout << "any of the timings \n" << std::endl;
	std::cout << "Our window is 500 by 500 pixels" << std::endl;
	std::cout << "We computed each pixel with a max number of iterations of 255" << std::endl;
	std::cout << "With a window range that centers the image with an aspect ratio of 1." << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Here are the runtimes." << std::endl;
    for (auto i =0u;i<timeDataArray.size();i++)
    {
        std::cout << "Mandelbrot set " << i + 1 << ": " << timeDataArray[i] << std::endl;
    }
    
    std::cout << "The Average runtime was: " << vectorAverage(timeDataArray) << std::endl;
    std::cout << "The Standard deviation was: " << vectorStandardDev(timeDataArray) << std::endl;

	// Now we are going to make a .ppm file.
	std::ofstream fout("output_image.ppm");

	fout << writeToFile.str();
	fout.close();
	std::cout << "Finished! " << std::endl;

	return 0;
}
