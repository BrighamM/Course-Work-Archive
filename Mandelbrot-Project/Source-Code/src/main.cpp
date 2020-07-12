#include <FracGui.h>


// argc is always the number of arguments that are given
// as input to the program. It is always at least one, 
// because the name of the program is always passed 
// as an argument.
/*
	So that means that: 
	argv[0] = ./Program_name
	argv[1] = whatever was passed after calling the program
	argv[argc] = null ALWAYS!
*/
int main(int argc, char *argv[]){
	

	if(argc > 0){
		for(int i = 0; i < argc; i++){
			std::cout << argv[i] << std::endl;
		}
	}

	FracGui runProgram;

	//std::cout<< "Hello from the flash test" << std::endl;
// This will create a file that is 200 pixels wide and 
// 300 pixels tall the third argument is what background do you want?
// 0.0 is Black and 1.0 is white
	//pngwriter image(200, 300, .5, "out.png");
// For this plot function we are plotting at 30,40 with rgb = 1,0,0 we
// can use either doubles from 0 to 1 or ints from 0 to 65535
//	image.plot(30, 40, 1.0, 0.0, 0.0);
//	image.close();

//	std::cout<< "Now commencing pixel class test"<< std::endl;
//	Pixel first;
//	Pixel second(.234,.543,.734);

	//first.printInfo();
	//second.printInfo();
//	PixelMap testSubject(5,5);
//	testSubject.printInfo();

	// FractalImageGenerator myProgram;

	// myProgram.run();
	
	return 0;
}


