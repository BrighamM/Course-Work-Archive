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



template<typename F>
double timefunc(F incomingFunct)
{



	auto start = std::chrono::steady_clock::now();
	incomingFunct();
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	return elapsed_seconds.count();









	//auto start = std::chrono::steady_clock::now();
	//incomingFunct();
	//auto end = std::chrono::steady_clock::now();
	//std::chrono::duration<double> elapsed_seconds = end - start;
	//return elapsed_seconds.count();

















	//std::chrono::time_point<std::chrono::system_clock> start, end;
	//start = std::chrono::steady_clock::now();

	//incomingFunct();

	//end = std::chrono::steady_clock::now();
	//std::chrono::duration<double> elapsed_seconds = end - start;
	//std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	//return elapsed_seconds.count();
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



int main()
{

	int imageWidth = 500;
	int imageHeight = 500;
	int maxN = 255;

	double minR = -2.1;
	double maxR = 1.1;
	double minI = -1.6;
	double maxI = 1.6;
	
	std::ostringstream writeToFile;

	//generateMandelbrotset(writeToFile, imageWidth, imageHeight, maxN, minR, maxR, minI, maxI);

	for (int i = 0; i < 15;i++)
	{
		std::cout << "elapsed time: " << timefunc([&](){generateMandelbrotset(writeToFile, imageWidth, imageHeight, maxN, minR, maxR, minI, maxI); }) << std::endl;
	}

	// Now we are going to make a .ppm file.
	std::ofstream fout("output_image.ppm");

	fout << writeToFile.str();
	fout.close();
	std::cout << "Finished! " << std::endl;

	return 0;
}