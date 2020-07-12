#ifndef PIXEL_H
#define PIXEL_H
#include <iostream>

class Pixel
{
private: 
	double redComponent;
	double greenComponent;
	double blueComponent;
public: 
	Pixel();
	Pixel(double,double,double);

	double getRedComponent();
	double getGreenComponent();
	double getBlueComponent();

	void setRedComponent(double);
	void setGreenComponent(double);
	void setBlueComponent(double);

	void setPixel(double,double,double);
	Pixel getPixel();

	void printPixelInfo();
};

#endif