#include <FracGui.h>

FracGui::FracGui()
{
    std::string choice;
	std::cout << system("clear");
	std::cout << std::endl;
	std::cout << "***************************************************" << std::endl;
	std::cout << "** Welcome to Brigham's fractal image generator! **" << std::endl;
	std::cout << "***************************************************" << std::endl;
	std::cout << "*                                                 *" << std::endl;
	std::cout << "* This is the beginning of the program!           *" << std::endl;
	std::cout << "* Please select fractal:                          *" << std::endl;
	std::cout << "*                                                 *" << std::endl;
	std::cout << "* A. MANDELBROT                                   *" << std::endl;
	std::cout << "* B. Quit the program                             *" << std::endl;
    std::cout << "* C. COMING SOON!                                 *" << std::endl;
	std::cout << "*                                                 *" << std::endl;
	std::cout << "***************************************************" << std::endl;
	std::cout << "What do you want to do? ";
	std::cin >> choice;
	if((choice == "a") || (choice == "A"))
	{
		this->executeMandelbrotOption();
	}
    if((choice == "b") || (choice == "B"))
	{
		return;
	}
    return;
}

void FracGui::executeMandelbrotOption()
{
    unsigned widthInPixels = 500;
    unsigned heightInPixels = 500;
    unsigned maxIterations = 255;
    double xCenterPoint = -.8;
    double yCenterPoint = 0;
    double minRectRadius = 1.5;


    std::string qInput;

    std::cout << system("clear");
	std::cout << std::endl;
	std::cout << "***************************************************" << std::endl;
	std::cout << "* Before we can generate pretty pictures we need  *" << std::endl;
	std::cout << "* some information.                               *" << std::endl;
    std::cout << "*                                                 *" << std::endl;
	std::cout << "* PRESS ENTER TO CONTINUE!                        *" << std::endl;
	std::cout << "***************************************************" << std::endl;

	std::cout << "Press enter to accept defaults!" << std::endl;
    std::cout << "What is the width of the image in pixels? [default = 500]";
    std::getline(std::cin, qInput);
    if(!qInput.empty()){
        std::istringstream stream(qInput);
        stream >> widthInPixels;
    }
    qInput = "";

    std::cout << "What is the height of the image in pixels? [default = 500]";
    std::getline(std::cin, qInput);
    if(!qInput.empty()){
        std::istringstream stream(qInput);
        stream >> heightInPixels;
    }
    qInput = "";

    std::cout << "What is the max number of iterations? [default = 255]";
    std::getline(std::cin, qInput);
    if(!qInput.empty()){
        std::istringstream stream(qInput);
        stream >> maxIterations;
    }
    qInput = "";

    std::cout << "What is the X-center point? [default = -.8]";
    std::getline(std::cin, qInput);
    if(!qInput.empty()){
        std::istringstream stream(qInput);
        stream >> xCenterPoint;
    }
    qInput = "";

    std::cout << "What is the Y-center point? [default = 0]";
    std::getline(std::cin, qInput);
    if(!qInput.empty()){
        std::istringstream stream(qInput);
        stream >> yCenterPoint;
    }
    qInput = "";

    std::cout << "If you don't know what this is just hit enter!" << std::endl;
    std::cout << "What is the minimum rectangular radius? [default = 1.5]";
    std::getline(std::cin, qInput);
    if(!qInput.empty()){
        std::istringstream stream(qInput);
        stream >> minRectRadius;
    }
    qInput = "";

    std::cout << "Now we are ready! hit enter to continue!" << std::endl;
    std::cin.ignore();

    MandelFracStatsOne statHolder(widthInPixels, 
                                    heightInPixels, 
                                    maxIterations, 
                                    xCenterPoint, 
                                    yCenterPoint, 
                                    minRectRadius);
    
    FractalImageGenerator mandelOne(statHolder);
}