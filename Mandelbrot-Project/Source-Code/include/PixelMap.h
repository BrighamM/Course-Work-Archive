#ifndef PIXEL_MAP_H
#define PIXEL_MAP_H
#include <Pixel.h>
#include <vector>

class PixelMap
{
private:
	unsigned pmRows;
	unsigned pmCols;

public:
	std::vector<std::vector<Pixel>> publicPixelMap;
	PixelMap(unsigned,unsigned);
	void printPixelMapInfo();
};

#endif