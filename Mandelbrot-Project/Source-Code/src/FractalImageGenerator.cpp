#include <FractalImageGenerator.h>

FractalImageGenerator::FractalImageGenerator()
{

}

FractalImageGenerator::FractalImageGenerator(MandelFracStatsOne inputStats)
{
	PixelMap masterPixelMap(inputStats.widthInPixels, inputStats.heightInPixels);

	// this->buildMandelbrotOneDataSet(masterPixelMap,
	// 					inputStats.widthInPixels,
	// 					inputStats.heightInPixels,
	// 					inputStats.maxIterations,
	// 					inputStats.minRealValue,
	// 					inputStats.maxRealValue,
	// 					inputStats.minImaginaryValue,
	// 					inputStats.maxImaginaryValue);
	std::cout << Stat_Util::timefunc([&](){buildMandelbrotOneDataSet(masterPixelMap,
						inputStats.widthInPixels,
						inputStats.heightInPixels,
						inputStats.maxIterations,
						inputStats.minRealValue,
						inputStats.maxRealValue,
						inputStats.minImaginaryValue,
						inputStats.maxImaginaryValue); }) << std::endl;;
	this->buildPNGFromPixelMap(masterPixelMap, inputStats.widthInPixels, inputStats.heightInPixels);
	// timeDataArray.push_back( timefunc([&](){generateMandelbrotset(writeToFile, imageWidth, imageHeight, maxN, minR, maxR,  minI, maxI); }));
}

void FractalImageGenerator::buildMandelbrotOneDataSet(PixelMap &mPMap,
												unsigned iwp,
												unsigned ihp,
												unsigned maxN,
												double minR,
												double maxR,
												double minI,
												double maxI)
{
	// x and "y" positions in the viewing plane
	double realX = 0;
	double imagI = 0;

	// iteration counter
	unsigned iterations = 0;

	// computed real and imaginary parts
	double zr;
	double zi;

	// for coloring
	unsigned r, g, b;
	double rr,rg,rb;

	// temp variable used in while loop
	double xTemp;

	for (unsigned y = 0; y < ihp; y++)
	{
		for (unsigned x = 0; x < iwp; x++)
		{
			// compute x and y
			realX = x * ((maxR - minR) / iwp) + minR;
			imagI = y * ((maxI - minI) / ihp) + minI;

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

			//r = iterations % 256;
			//g = iterations % 256;
			//b = iterations % 256;

			r = (unsigned)((float)iterations*sinf((float)iterations)) % (maxN+1);
			g = (iterations*iterations) % (maxN+1);
			b = iterations % (maxN+1);
			rr = (double)(r/maxN);
			rg = (double)(g/maxN);
			rb = (double)(b/maxN);

			mPMap.publicPixelMap[x][y].setPixel(rr,rg,rb);

			// refstring << r << " " << g << " " << b << " ";
		}
		// refstring << std::endl;
		// std::cout << y << std::endl;
	}

}

void FractalImageGenerator::buildPNGFromPixelMap(PixelMap &mapToBuild, unsigned imageWidth, unsigned imageHeight)
{
	// This will create a file that is 200 pixels wide and 
	// 300 pixels tall the third argument is what background do you want?
	// 0.0 is Black and 1.0 is white
	pngwriter image(imageWidth, imageHeight, .5, "out.png");
	// For this plot function we are plotting at 30,40 with rgb = 1,0,0 we
	// can use either doubles from 0 to 1 or ints from 0 to 65535
	//	image.plot(30, 40, 1.0, 0.0, 0.0);
	for (unsigned y = 0; y < imageHeight; y++)
	{
		for (unsigned x = 0; x < imageWidth; x++)
		{
			image.plot(x, y, mapToBuild.publicPixelMap[x][y].getRedComponent(),
							mapToBuild.publicPixelMap[x][y].getGreenComponent(),
							mapToBuild.publicPixelMap[x][y].getBlueComponent());
		}
	}
	
	image.close();
}
