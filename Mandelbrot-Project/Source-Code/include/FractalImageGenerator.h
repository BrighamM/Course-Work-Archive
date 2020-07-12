#ifndef FRACTAL_IMAGE_GENERATOR_H
#define FRACTAL_IMAGE_GENERATOR_H
#include <PixelMap.h>
#include <stdlib.h>
#include <string>
#include <pngwriter.h>
#include <Stat_Util.h>
#include <MandelFracStatsOne.h>

class FractalImageGenerator
{
private:
	void buildMandelbrotOneDataSet(PixelMap&, unsigned, unsigned, unsigned, double, double, double, double);
	void buildPNGFromPixelMap(PixelMap&, unsigned, unsigned);

public:
	FractalImageGenerator();
	FractalImageGenerator(MandelFracStatsOne);
};

#endif
