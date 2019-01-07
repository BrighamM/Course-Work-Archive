
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
#include "M_Image.h"
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

	private: 
		std::mutex m;
		std::queue<T> q;
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


class ThreadPool
{
	public:
		using func = std::function<void(void)>;
		ThreadPool(int n):pool(n),queue(),hasItem(),itemMutex(),shouldContinue(true)
	{
		for(auto&t:pool)
		{
			t = std::thread([&](){this->run();});
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
			threadWork++;
			hasItem.notify_one();
			
		}
		void run()
		{

			while(shouldContinue)
			{
				func f;

				while(queue.try_dequeue(f))
				{
					//f = queue.dequeue();
					threadWork--;

					if(threadWork <=  0)
					{

						this->stop();	
					}
					//std::unique_lock<std::mutex> l(itemMutex);
					//hasItem.wait(l);
				
					if(!shouldContinue)
					{
						return;
					}
					f();	
				}
				//f();
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
		std::condition_variable caughtUp;
		int numTasksGiven;
		int numTasksFinsished;
		std::mutex jobMutex;
		std::mutex taskFinishedMutex;
		std::mutex taskAddedMutex;
};





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




void threadPoolPlayGround(M_Image &uI,int workingThreads)
{
	//For this method we are going to break up the image into its specific "rows" of work

	//First we find the total Y distance and break that up by the number of rows.
	double totalY = fabs(uI.minI) + fabs(uI.maxI);

	// now we divide the totalY by the number of rows to get the increment in y per row
	double yIncr = totalY/((double)uI.imageHeightpx);

	//Make a string stream vector so each row has its own piece of data to write to.
	std::vector<std::ostringstream> dividedString(uI.imageHeightpx);




	ThreadPool pool(workingThreads);



	//Make a Thread-Safe queue
	//TSQ<std::function<void(void)>> threadQ;

	//std::cout << workingThreads << std::endl; 

	//Now I think we are ready to load the queue
	//ThreadPool tPool(workingThreads);

	for(int i = 0;i<uI.imageHeightpx;i++)
	{
		pool.post(std::function<void(void)>([&,i,yIncr](){generateMandelbrotset(
						dividedString[i],uI.imageWidthpx,1,uI.maxN,uI.minR,uI.maxR,(uI.maxI - yIncr) - (i*yIncr),(uI.maxI-(i*yIncr))
						);}));
	}

	/*	
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
	work++;
	if(work >= uI.imageHeightpx)
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

	 */






	for(int i = 0;i<uI.imageHeightpx;i++)
	{
		std::cout << dividedString[i].str();
		uI.writeToFile << dividedString[i].str(); 
	}

}





int main()
{

	// set up the input parameters to the mandelbrot function

	auto imageWidth = 500;
	auto imageHeight = 500;
	auto maxN =  255;
	//auto nData = 15;
	auto minR = -2.1;
	auto maxR = 1.1;
	auto minI = -1.6;
	auto maxI = 1.6;
	// First we find out how many threads we have, then we are going to use up to twice that number.
	auto threadCount = std::thread::hardware_concurrency();
	threadCount = threadCount*2;

	M_Image userImage(imageWidth,imageHeight,maxN,minR,maxR,minI,maxI);


	userImage.writeToFile << "P3" << std::endl;
	userImage.writeToFile << userImage.imageWidthpx << " " << userImage.imageHeightpx << std::endl;
	userImage.writeToFile << "256" << std::endl;




  threadWork = 0;
	threadPoolPlayGround(userImage , 1);




	/*
	// Now that we have a function where we just have to provide a number of threads to use
	// We are ready to gather data. 


	// vector to hold times for the various runtimes.
	std::vector<double> timeDataArray;

	// Run through the threadcounts and obtain stats for 50 runs.
	for(unsigned i = 1;i<=threadCount;i++)
	{
	for(int j = 0;j<nData;j++)
	{
	userImage.writeToFile.str("");
	userImage.writeToFile.clear();
	userImage.writeToFile << "P3" << std::endl;
	userImage.writeToFile << userImage.imageWidthpx << " " << userImage.imageHeightpx << std::endl;
	userImage.writeToFile << "256" << std::endl;

	timeDataArray.push_back(timefunc([&](){threadPoolPlayGround(userImage,i);}));
	}
	std::cout << "\nThis run was testing " << (i)  << " threads. " << std::endl;
	std::cout << "For " << nData  << " runs with " << (i) << " threads. "  << std::endl;
	std::cout << "The Average runtime was: " << vectorAverage(timeDataArray) << std::endl;	
	std::cout << "The Standard Deviation was: " << vectorStandardDev(timeDataArray) << std::endl << std::endl;
	timeDataArray.clear();
	}
	 */




	// The last run will produce an image made from 8 threads.
	// Now we are going to make a .ppm file.
	std::ofstream fout("output_image.ppm");
	fout << userImage.writeToFile.str();
	fout.close();
	std::cout << "Finished! " << std::endl;

	return 0;
}
