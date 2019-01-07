
#include <thread>
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
			realX = minR + (x*((maxR - minR)/(imageWidth)));
			imagI = maxI - (y*((maxI - minI)/(imageHeight)));
		
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


// Given a number of threads to use this method will make a Mandelbrot image from multiple threads.
void threadedMandelbrot(int threadC,std::ostringstream &refString,int imageWidth,int imageHeight,int maxN,double minR,double maxR,double minI,double maxI)
{
	
	// Generate the bounds to run the parallel code on 
	std::vector<int> imagePHeights;
	std::vector<double> imageYvals;

	for (int i = 0; i < (threadC+1); i++)
	{
		imagePHeights.push_back(imageHeight/(i+1));	
	}

	// done calculating pixel counts for all applicable thread sizes
	double totalY = fabs(minI) + fabs(maxI);
	for (int i = 0;i < (threadC+1); i++)
	{
		imageYvals.push_back(totalY/((double)(i+1)));
	}
	// Finished generation of Bounds to split up the parallel work





	// Write the preliminaries to the string
	refString.str("");
	refString.clear();
	refString << "P3" << std::endl;
	refString << imageWidth << " " << ((imagePHeights[threadC])*(threadC+1)) << std::endl;
	refString << "256" << std::endl;
	
	//Operate and work accordingly
	if(threadC == 0)
	{
		generateMandelbrotset(refString,imageWidth,imageHeight,maxN,minR,maxR,minI,maxI);
		return;
	}
	
	// divideString is the vector of OSS objects that will be split so that each
	// thread has it's own individual thing to write to.
	std::vector<std::ostringstream> dividedString(threadC+1);
	std::vector<std::thread> threads(threadC+1);

	for(unsigned i=0;i<threads.size();++i)
	{
		threads[i] = std::thread([&,i](){generateMandelbrotset(dividedString[i],imageWidth,imagePHeights[threadC],maxN,minR,maxR,(maxI-((i+1)*imageYvals[threadC])),(maxI-(i*imageYvals[threadC])));});
	}

	for(auto && element:threads)
	{
		element.join();
	}

	for(unsigned i = 0;i<threads.size();i++)
	{
		refString << dividedString[i].str();
	}

	return;
}

int main()
{
	// set up the input parameters to the mandelbrot function
	auto imageWidth = 500;
	auto imageHeight = 500;
	auto maxN =  255;
	auto nData = 50;
	auto minR = -2.1;
	auto maxR = 1.1;
	auto minI = -1.6;
	auto maxI = 1.6;
	// First we find out how many threads we have, then we are going to use up to twice that number.
	auto threadCount = std::thread::hardware_concurrency();
	threadCount = threadCount*2;

	// Prepare the stringstream object for in program writing.
	std::ostringstream writeToFile;
	
	// Now that we have a function where we just have to provide a number of threads to use
	// We are ready to gather data. 
	
 
	// vector to hold times for the various runtimes.
	std::vector<double> timeDataArray;

	// Run through the threadcounts and obtain stats for 50 runs.
	for(unsigned i = 0;i<threadCount;i++)
	{
		for(int j = 0;j<nData;j++)
		{
			timeDataArray.push_back(timefunc([&](){threadedMandelbrot(i,writeToFile,imageWidth,imageHeight,maxN,minR,maxR,minI,maxI);}));
		}
		std::cout << "\nThis run was testing " << (i + 1)  << " threads. " << std::endl;
		std::cout << "For " << nData  << " runs with " << (i + 1) << " threads. "  << std::endl;
		std::cout << "The Average runtime was: " << vectorAverage(timeDataArray) << std::endl;	
		std::cout << "The Standard Deviation was: " << vectorStandardDev(timeDataArray) << std::endl << std::endl;
		timeDataArray.clear();
	}
	// The last run will produce an image made from 8 threads.
	// Now we are going to make a .ppm file.
	std::ofstream fout("output_image.ppm");
	fout << writeToFile.str();
	fout.close();
	std::cout << "Finished! " << std::endl;

	return 0;
}
