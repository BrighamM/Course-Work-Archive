#include <PixelMap.h>

PixelMap::PixelMap(unsigned width, unsigned height)
{
	this->pmCols = width;
	this->pmRows = height;
	for(unsigned ui = 0; ui < this->pmCols; ui++)
	{
		std::vector<Pixel> tempVector;
		for(unsigned uj = 0; uj < this->pmRows; uj++)
		{
			tempVector.push_back(Pixel());
		}
		this->publicPixelMap.push_back(tempVector);
	}
}

void PixelMap::printPixelMapInfo()
{
	std::cout<<"For this we are going to print the matrix!"<< std::endl;
	std::cout<<"Make sure to use a small matrix for printing!"<< std::endl;
	std::cout<<"The width of the matrix is: " << this->pmCols << std::endl;
	std::cout<<"The height of the matrix is: " << this->pmRows << std::endl;
	std::cout<<"Once you press enter the matrix will be displayed!"<< std::endl;
	std::cin.ignore();
	for(unsigned urow = 0; urow < this->publicPixelMap.size(); urow++)
	{
		for(unsigned ucol = 0; ucol < this->publicPixelMap[urow].size(); ucol++)
		{
			std::cout<<"******" << std::endl;
			std::cout<<"*    *" << std::endl;
			std::cout<<"*    *" << std::endl;
			std::cout<<"*    *" << std::endl;
			std::cout<<"*    *" << std::endl;
			std::cout<<"******" << std::endl;
			std::cout<<"The Index is ui,uj: " << urow << "," << ucol << " " << std::endl;
			publicPixelMap[ucol][urow].printPixelInfo();
		}
	}

	std::cout<<"* Press enter to continue! *" << std::endl;
	std::cin.ignore();
}
