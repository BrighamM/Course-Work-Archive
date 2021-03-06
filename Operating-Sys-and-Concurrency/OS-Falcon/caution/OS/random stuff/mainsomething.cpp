
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
#include <queue>
#include <mutex>
//#include "TSQ.h"
#include "M_Image.h"
//#include "ThreadPool.h"
#include <atomic>
#include <map>
#include <condition_variable>


std::atomic<int> threadWork(0);

template<typename T>
class TSQ
{
	public:
		void enqueue(T t)
		{
			std::lock_guard<std::mutex> l(m);
			q.push(t);
		}

		//template<typename Ts..>
		//void emplace(..Ts args){enqueue(T(..args));}

		T dequeue()
		{
			std::lock_guard<std::mutex> l(m);
			auto res = q.front();
			q.pop();
			return res;
		}

		bool try_dequeue(T& res)
		{
			std::lock_guard<std::mutex> l(m);
			if(q.empty()) 
			{
				return false;
			}
			res = q.front();
			q.pop();
			return true;
		}

		bool isEmpty()
		{
			return q.empty();
		}

	private: 
		std::mutex m;
		std::queue<T> q;
};




class ThreadPool
{
public:
	using func = std::function<void(void)>;
	ThreadPool(int n):pool(n),queue(),hasItem(),itemMutex(),shouldContinue(true)
	{
		for(auto&t:pool)
		{
			t = std::thread([=](){this->run();});
		}
	}

	void stop()
	{
		shouldContinue = false;
		hasItem.notify_all();
	}

	void post(func f)
	{
		queue.enqueue(f);
		hasItem.notify_one();	
	}

	void run()
	{
		while(shouldContinue)
		{
			func f;
			while(!queue.try_dequeue(f))
			{
				std::unique_lock<std::mutex> l(itemMutex);
				hasItem.wait(l);
				if(!shouldContinue)
				{
					return;
				}	
			}
			//threadWork--;
			f();
			if(queue.isEmpty())
			{
				this->stop();
			}
		}
	}

	~ThreadPool()
	{
		for(auto &t:pool)
		{
			t.join();
		}
	}
private:
	std::vector<std::thread> pool;
	TSQ<func> queue;
	std::condition_variable hasItem;
	std::mutex itemMutex;
	std::atomic<bool> shouldContinue;
};
































 
/*
	 class ThreadPool
	 {

	 public:
	 ThreadPool(int n):q(),pool(n),shouldContinue(false)
	 {
	 for(auto& t:pool)
	 {
	 t = std::thread([&]()
	 {
	 while(shouldContinue)
	 {
	 std::function<void(void)> task;
	 auto has_task = q.try_dequeue(task);
	 if(!shouldContinue)
	 {
	 return;
	 }
	 if(has_task)
	 {
	 task();
	 }
	 }
	 });
	 }
	 }

	 ~ThreadPool()
	 {
	 for(auto &t:pool)
	 {
	 t.join();
	 }
	 }

	 void post(std::function<void(void)> f,int id)
	 {
	 {//Critical Section
	 std::lock_guard<std::mutex> l(m);
	 counts[id] =+ 1;	
	 }
	 q.enqueue(f);
	 }
	 void then(std::function<void(void)> f,int id)
	 {
	 std::lock_guard<std::mutex> l(m);
	 continuations[id] = f;
	 }
	 void stop()
	 {
	 shouldContinue = false;
	 }

	 private:
	 TSQ<std::function<void(void)>> q;
	 std::vector<std::thread> pool;
	 std::atomic<bool> shouldContinue;
	 std::map<int,int> counts;
	 std::map<int,std::function<void(void)>> continuations;
	 std::mutex m;
	 };
 */



/*
	 Now it is time for a think...
	 For starters and to get this done perhaps by tomorrow, lets not use the threadpool class.
	 ... we will unqueue

 */









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
		//	std::cout << r << " " << g << " " << b << " "  << std::endl;
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






void threadPoolNrowByNrow(M_Image &uI,int nRows,int workingThreads)
{


	double totalY = fabs(uI.minI) + fabs(uI.maxI);

	// now we divide the totalY by the number of rows to get the increment in y per row
	double yIncr = totalY/((double)uI.imageHeightpx);
	

	int nChunks = uI.imageHeightpx/nRows;

	if((uI.imageHeightpx%nRows) > 0)
	{
		std::cout << "You need to deal with this... hit 'enter'" << std::endl;
		std::cin.ignore();
	}


	//Make a string stream vector so each row has its own piece of data to write to.
	std::vector<std::ostringstream> dividedString(nChunks);

	//Make a Thread-Safe queue
	TSQ<std::function<void(void)>> threadQ;

	//Now I think we are ready to load the queue
	//ThreadPool tPool(workingThreads);

	std::atomic<int> work(0); 
	for(int i = 0;i<nChunks;i++)
	{
		threadQ.enqueue(std::function<void(void)>([&,i](){generateMandelbrotset(
		dividedString[i],
		uI.imageWidthpx,nRows,uI.maxN,uI.minR,uI.maxR,(uI.maxI - yIncr*nRows) - i*yIncr*nRows,uI.maxI - (i*nRows*yIncr)
		);}));
		work++;	
	}
  
	bool shouldContinue = true;
	std::vector<std::thread> pool(workingThreads);


	for(auto& t:pool)
	{
		t = std::thread([&]()
			{
				while(shouldContinue)
				{
					std::function<void(void)> task;
					//auto has_task = threadQ.try_dequeue(task);
					task = threadQ.dequeue();
					work--;	
					if(work < 10)
					{
						shouldContinue = false;
					}
					if(!shouldContinue)
					{
						break;
						//return;
					}
					
					task();
						
					
				}
			});
	}

	for(auto &t:pool)
	{
		t.join();
	}

	for(int i = 0;i<nChunks;i++)
	{
		uI.writeToFile << dividedString[i].str(); 
	}

}




































void threadPoolSubrowBySubrow(M_Image &uI,int workingThreads)
{


	double totalY = fabs(uI.minI) + fabs(uI.maxI);

	// now we divide the totalY by the number of rows to get the increment in y per row
	double yIncr = totalY/((double)uI.imageHeightpx);
	
	//double totalX = fabs(uI.minR) + fabs(uI.maxR);

	//double xIncr = totalX/((double)uI.imageWidthpx);


	double xMid = ((fabs(uI.minR) + fabs(uI.maxR))/2.0);
	//Make a string stream vector so each row has its own piece of data to write to.
	std::vector<std::ostringstream> dividedString(uI.imageHeightpx *2);

	//Make a Thread-Safe queue
	TSQ<std::function<void(void)>> threadQ;

	//Now I think we are ready to load the queue
	//ThreadPool tPool(workingThreads);
	std::atomic<int> work(0); 
	for(int i = 0;i<uI.imageWidthpx;i++)
	{
		for(int j = 0;j<2;j++)
		{
			threadQ.enqueue(std::function<void(void)>([&,i,j](){generateMandelbrotset(
			dividedString[(2*i)+j],
		//	uI.imageWidth/2,1,uI.maxN,(uI.minR+(j*xIncr)),((uI.minR + xIncr) + (j*xIncr)),(uI.maxI - yIncr) - (i*yIncr),(uI.maxI-(i*yIncr))
			
			uI.imageWidthpx/2,1,uI.maxN,uI.minR+(j*xMid),((uI.minR+xMid)+(j*xMid)),(uI.maxI - yIncr) - (i*yIncr),(uI.maxI-(i*yIncr))
			);}));
			work++;	
		}
	}
  
	bool shouldContinue = true;
	std::vector<std::thread> pool(workingThreads);


	for(auto& t:pool)
	{
		t = std::thread([&]()
			{
				while(shouldContinue)
				{
					std::function<void(void)> task;
					//auto has_task = threadQ.try_dequeue(task);
					task = threadQ.dequeue();
					work--;	
					if(work < 10)
					{
						shouldContinue = false;
					}
					if(!shouldContinue)
					{
						break;
						//return;
					}
					
					task();
						
					
				}
			});
	}

	for(auto &t:pool)
	{
		t.join();
	}

	for(int i = 0;i<uI.imageWidthpx;i++)
	{
		for(int j = 0;j<2;j++)
		{
			uI.writeToFile << dividedString[2*i+j].str(); 
		}
		uI.writeToFile << std::endl;
	}

}



















void threadPoolPixelByPixel(M_Image &uI,int workingThreads)
{
	//For this method we are going to break up the image into its specific "rows" of work

	//First we find the total Y distance and break that up by the number of rows.
	double totalY = fabs(uI.minI) + fabs(uI.maxI);

	// now we divide the totalY by the number of rows to get the increment in y per row
	double yIncr = totalY/((double)uI.imageHeightpx);
	
	double totalX = fabs(uI.minR) + fabs(uI.maxR);

	double xIncr = totalX/((double)uI.imageWidthpx);

	//Make a string stream vector so each row has its own piece of data to write to.
	std::vector<std::ostringstream> dividedString(uI.imageHeightpx * uI.imageWidthpx);

	//Make a Thread-Safe queue
	TSQ<std::function<void(void)>> threadQ;

	//Now I think we are ready to load the queue
	//ThreadPool tPool(workingThreads);
	std::atomic<int> work(0); 
	for(int i = 0;i<uI.imageHeightpx;i++)
	{
		for(int j = 0;j<uI.imageWidthpx;j++)
		{
			threadQ.enqueue(std::function<void(void)>([&,i,j](){generateMandelbrotset(
			dividedString[uI.imageWidthpx*i+j],
			1,1,uI.maxN,(uI.minR+(j*xIncr)),((uI.minR + xIncr) + (j*xIncr)),(uI.maxI - yIncr) - (i*yIncr),(uI.maxI-(i*yIncr))
			);}));
			work++;	
		}
	}
  
	bool shouldContinue = true;
	std::vector<std::thread> pool(workingThreads);


	for(auto& t:pool)
	{
		t = std::thread([&]()
			{
				while(shouldContinue)
				{
					std::function<void(void)> task;
					//auto has_task = threadQ.try_dequeue(task);
					task = threadQ.dequeue();
					work--;	
					if(work < 10)
					{
						shouldContinue = false;
					}
					if(!shouldContinue)
					{
						break;
						//return;
					}
					
					task();
						
					
				}
			});
	}

	for(auto &t:pool)
	{
		t.join();
	}

	for(int i = 0;i<uI.imageHeightpx;i++)
	{
		for(int j = 0;j<uI.imageWidthpx;j++)
		{
			uI.writeToFile << dividedString[uI.imageWidthpx*i + j].str(); 
		}
		uI.writeToFile << std::endl;
	}

}


void threadPoolRowByRow(M_Image &uI,int workingThreads)
{
	//For this method we are going to break up the image into its specific "rows" of work

	//First we find the total Y distance and break that up by the number of rows.
	double totalY = fabs(uI.minI) + fabs(uI.maxI);

	// now we divide the totalY by the number of rows to get the increment in y per row
	double yIncr = totalY/((double)uI.imageHeightpx);

	//Make a string stream vector so each row has its own piece of data to write to.
	std::vector<std::ostringstream> dividedString(uI.imageHeightpx);
	

	ThreadPool thePool(workingThreads);


	for(int i = 0;i<uI.imageHeightpx;i++)
	{
		thePool.post(std::function<void(void)>([&,i](){generateMandelbrotset(
		dividedString[i],uI.imageWidthpx,1,uI.maxN,uI.minR,uI.maxR,(uI.maxI - yIncr) - (i*yIncr),(uI.maxI-(i*yIncr))
		);}));
		//threadWork++;
	}	

	//std::cout << "3" << std::endl;
	//std::cin.ignore();

	//while(true)
	//{
	//	if(threadWork == 0) 
	//	{
	//		break;
	//	}
	//}

	thePool.run();

	/*



	//Make a Thread-Safe queue
	TSQ<std::function<void(void)>> threadQ;
		
	std::atomic<int> work(0); 
	for(int i = 0;i<uI.imageHeightpx;i++)
	{
		threadQ.enqueue(std::function<void(void)>([&,i](){generateMandelbrotset(
		dividedString[i],uI.imageWidthpx,1,uI.maxN,uI.minR,uI.maxR,(uI.maxI - yIncr) - (i*yIncr),(uI.maxI-(i*yIncr))
		);}));
		work++;
	}
 
	bool shouldContinue = true;
	std::vector<std::thread> pool(workingThreads);

	for(auto& t:pool)
	{
		t = std::thread([&]()
			{
				while(shouldContinue)
				{
					std::function<void(void)> task;
					//auto has_task = threadQ.try_dequeue(task);
					task = threadQ.dequeue();
					work--;
					if(work < 10 )
					{
						shouldContinue = false;
					}
					if(!shouldContinue)
					{
						break;
						//return;
					}
					task();
				}
			});
	}
for(auto &t:pool)
	{
		t.join();
	}

*/





	for(int i = 0;i<uI.imageHeightpx;i++)
	{
		uI.writeToFile << dividedString[i].str(); 
	}
}





int main()
{
/*
**********************************************************************************************************8
note endl change to main mandelbrot function

*/
	// set up the input parameters to the mandelbrot function

	auto imageWidth = 500;
	auto imageHeight = 500;
	auto maxN =  255;
	auto nData = 5;
	auto minR = -2.1;
	auto maxR = 1.1;
	auto minI = -1.6;
	auto maxI = 1.6;
	// First we find out how many threads we have, then we are going to use up to twice that number.
	auto threadCount = std::thread::hardware_concurrency();
	threadCount = threadCount*2;

	M_Image userImage(imageWidth,imageHeight,maxN,minR,maxR,minI,maxI);



	std::vector<double> timeDataArray;
	






/*



//multirow by multi row  implementation

	for(int i = 1; i<9;i++)
	{
		for(int j = 0;j<nData;j++)
		{	
			userImage.writeToFile.str(std::string());
			userImage.writeToFile << "P3" << std::endl;
			userImage.writeToFile << userImage.imageWidthpx << " " << userImage.imageHeightpx << std::endl;
			userImage.writeToFile << "256" << std::endl;	
			timeDataArray.push_back(timefunc([&,i](){threadPoolNrowByNrow(userImage,5,i);}));
		}	
		std::cout << "\nThis run was testing " << (i)  << " threads. " << "On a 5 row chunk by 5 row chunk scheme. " << std::endl;
		std::cout << "For " << nData  << " runs with " << (i) << " threads. "  << std::endl;
		std::cout << "The Average runtime was: " << vectorAverage(timeDataArray) << std::endl;	
		std::cout << "The Standard Deviation was: " << vectorStandardDev(timeDataArray) << std::endl << std::endl;
		timeDataArray.clear();
	}










//subRow by subRow implementation

	for(int i = 1; i<9;i++)
	{
		for(int j = 0;j<nData;j++)
		{	
			userImage.writeToFile.str(std::string());
			userImage.writeToFile << "P3" << std::endl;
			userImage.writeToFile << userImage.imageWidthpx << " " << userImage.imageHeightpx << std::endl;
			userImage.writeToFile << "256" << std::endl;	
			timeDataArray.push_back(timefunc([&,i](){threadPoolSubrowBySubrow(userImage,i);}));
		}	
		std::cout << "\nThis run was testing " << (i)  << " threads. " << "On a subrow by subrow scheme. "  << std::endl;
		std::cout << "For " << nData  << " runs with " << (i) << " threads. "  << std::endl;
		std::cout << "The Average runtime was: " << vectorAverage(timeDataArray) << std::endl;	
		std::cout << "The Standard Deviation was: " << vectorStandardDev(timeDataArray) << std::endl << std::endl;
		timeDataArray.clear();
	}






// Pixel by Pixel implementation
	for(int i = 1; i<9;i++)
	{
		for(int j = 0;j<nData;j++)
		{	
			userImage.writeToFile.str(std::string());
			userImage.writeToFile << "P3" << std::endl;
			userImage.writeToFile << userImage.imageWidthpx << " " << userImage.imageHeightpx << std::endl;
			userImage.writeToFile << "256" << std::endl;	
			timeDataArray.push_back(timefunc([&,i](){threadPoolPixelByPixel(userImage,i);}));
		}	
		std::cout << "\nThis run was testing " << (i)  << " threads. " << "On a pixel by pixel scheme. " << std::endl;
		std::cout << "For " << nData  << " runs with " << (i) << " threads. "  << std::endl;
		std::cout << "The Average runtime was: " << vectorAverage(timeDataArray) << std::endl;	
		std::cout << "The Standard Deviation was: " << vectorStandardDev(timeDataArray) << std::endl << std::endl;
		timeDataArray.clear();
	}
*/



//Row by Row implementation

	for(int i = 1; i<9;i++)
	{
		for(int j = 0;j<nData;j++)
		{	
			userImage.writeToFile.str(std::string());
			userImage.writeToFile << "P3" << std::endl;
			userImage.writeToFile << userImage.imageWidthpx << " " << userImage.imageHeightpx << std::endl;
			userImage.writeToFile << "256" << std::endl;	
			timeDataArray.push_back(timefunc([&,i](){threadPoolRowByRow(userImage,i);}));
		}	
		std::cout << "\nThis run was testing " << (i)  << " threads. " << "On a row by row scheme. " << std::endl;
		std::cout << "For " << nData  << " runs with " << (i) << " threads. "  << std::endl;
		std::cout << "The Average runtime was: " << vectorAverage(timeDataArray) << std::endl;	
		std::cout << "The Standard Deviation was: " << vectorStandardDev(timeDataArray) << std::endl << std::endl;
		timeDataArray.clear();
		std::ofstream fout("output_image.ppm");
		fout << userImage.writeToFile.str();
		fout.close();
		std::cout << " press enter " << std::endl;
		std::cin.ignore();
	}



	// The last run will produce an image made from 8 threads.
	// Now we are going to make a .ppm file.
	//std::ofstream fout("output_image.ppm");
	//fout << userImage.writeToFile.str();
	//fout.close();
	std::cout << "Finished! " << std::endl;

	return 0;
}


