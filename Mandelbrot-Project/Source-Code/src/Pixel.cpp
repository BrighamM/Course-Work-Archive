#include <Pixel.h>

Pixel::Pixel()
{
	this->redComponent = 0.0;
	this->greenComponent = 0.0;
	this->blueComponent = 0.0;	
}

Pixel::Pixel(double red, double green, double blue)
{
	this->redComponent = red;
	this->greenComponent = green;
	this->blueComponent = blue;
}

double Pixel::getRedComponent()
{
	return this->redComponent;
}

double Pixel::getGreenComponent()
{
	return this->greenComponent;
}

double Pixel::getBlueComponent()
{
	return this->blueComponent;
}

void Pixel::setRedComponent(double red)
{
	this->redComponent = red;
}

void Pixel::setGreenComponent(double green)
{
	this->greenComponent = green;
}

void Pixel::setBlueComponent(double blue)
{
	this->blueComponent = blue;
}

void Pixel::setPixel(double redValue, double greenValue, double blueValue)
{
	this->setRedComponent(redValue);
	this->setGreenComponent(greenValue);
	this->setBlueComponent(blueValue);
}

Pixel Pixel::getPixel()
{
	return *this;
}

void Pixel::printPixelInfo()
{
	std::cout<< "Pixel info!" << std::endl;
	std::cout<< "The Red Value is   : " << this->redComponent << std::endl;
	std::cout<< "The Green Value is : " << this->greenComponent << std::endl;
	std::cout<< "The Blue Value is  : " << this->blueComponent << std::endl;
}





