

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
//nclude "TSQ.h"
//nclude "ThreadPool.h"
#include <atomic>
#include <map>
#include <condition_variable>
#include <cstdlib>
#include <ctime>



std::atomic<int> threadWork(0);
int address = -1;

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
			std::lock_guard<std::mutex> l(m);
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
	ThreadPool(int n):taskCounter(0),pool(n),queue(),taskCounter_m(),done(false)
	{
	}
 
	void stop()
	{
		done = true;
	}
	
	void post(func f)
	{
		queue.enqueue(f);
		{
			std::lock_guard<std::mutex> l(taskCounter_m);
			taskCounter++;
		}
	}
	
	void start()
	{
		for(auto &t:pool)
		{
			t = std::thread([&](){run();});
			// could join here
		}
		for(auto &t:pool)
		{
			t.join();
		}
	}

	void run()
	{
		while(!done)
		{
			func f;
			if(queue.try_dequeue(f))
			{
				f();
				{
					std::lock_guard<std::mutex> l(taskCounter_m);
					taskCounter--;
				}
				if(taskCounter <= 0)
				{
					stop();
				}
			}
			if(done)
			{
				return;
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
int taskCounter;
std::vector<std::thread> pool;
TSQ<func> queue;
std::mutex taskCounter_m;
std::atomic<bool> done;

};


ThreadPool thread2(2);





/*
	parallelQ.enqueue(std::function<void(void)>([&](){
	parallelQuickSort(vect,0,vect.size()-1);
	}));
	qSortWork++;

	std::mutex counterMutex;	
	
	bool shouldContinue = true;
	std::vector<std::thread> pool(threads);

	for(auto& t:pool)
	{
		t = std::thread([&]()
			{
				while(shouldContinue)
				{
					std::function<void(void)> task;
					if(parallelQ.try_dequeue(task))
					{
						task();
						{
							std::lock_guard<std::mutex> l(counterMutex);
							qSortWork--;
							//std::cout<< qSortWork << " "  << std::endl;
							//std::cin.ignore();
						}
						if(qSortWork <= 0)//if basecase stop posting and if zero you are done)
						{
							shouldContinue = false;
						}
					}
					if(!shouldContinue)
					{
						break;
					}
				}
			});
	}

	for(auto &t:pool)
	{
		t.join();
	}


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

void fillVector(std::vector<int> &inVector, int size)
{
	unsigned seed;
	seed = time(0);
	srand(seed);

	for(int i=0;i<size;i++)
	{
		inVector.push_back(rand());
	}
}

void vectorSort(std::vector<int> &svec)
{
	std::sort(svec.begin(),svec.end());
}

auto vectorFind(std::vector<int> &svec, int item)
{
	std::vector<int>::iterator it;
	it = find (svec.begin(),svec.end(),item);
	auto index = std::distance(svec.begin(),it);
	return index;
}

void stdStatsGiver(std::vector<int> &svec,int maxN,int item)
{
	std::vector<double> vData;

	for(int i = 0; i<maxN;i++)
	{
		if(svec[vectorFind(svec,item)] != item)
		{
			std::cout << "ERROR! " << std::endl;
		}
    vData.push_back(timefunc([&,i](){vectorFind(svec,item);}));
	}
	std::cout << "For " << maxN  << " runs and size " << svec.size() << std::endl;
	std::cout << "The Average SEARCH time was: " << vectorAverage(vData) << std::endl;	
	std::cout << "The Standard Deviation was: " << vectorStandardDev(vData) << std::endl << std::endl;
	vData.clear();

	for(int i = 0; i<maxN-1;i++)
	{
		std::vector<int> vCData(svec);
    vData.push_back(timefunc([&,i](){vectorSort(vCData);}));
	}
	vData.push_back(timefunc([&](){vectorSort(svec);}));
	std::cout << "For " << maxN  << " runs and size " << svec.size()  << std::endl;
	std::cout << "The Average SORT time was: " << vectorAverage(vData) << std::endl;	
	std::cout << "The Standard Deviation was: " << vectorStandardDev(vData) << std::endl << std::endl;
	vData.clear();
}

void pSearch(std::vector<int> &vect,int item,int begin,int end)
{
	for(int i = begin;i<= end;i++)
	{
		if(vect[i] == item)
		{
			address = i;
		}
	}
}

int threadedVectorFind(std::vector<int> &vect,int item,int threads)
{
	address = -1;
	//Make a Thread-Safe queue
	TSQ<std::function<void(void)>> threadQ;
	std::mutex counterMutex;	
	std::atomic<int> work(0); 
	for(int i = 0;i<10;i++)
	{
		threadQ.enqueue(std::function<void(void)>([&,i](){
		pSearch(vect,item,i*(vect.size()/10),(((i+1)*(vect.size()/10))-1));
		}));
		work++;
	}
	bool shouldContinue = true;
	std::vector<std::thread> pool(threads);
	for(auto& t:pool)
	{
		t = std::thread([&]()
			{
				while(shouldContinue)
				{
					std::function<void(void)> task;
					if(threadQ.try_dequeue(task))
					{
						task();
						{
							std::lock_guard<std::mutex> l(counterMutex);
							work--;
						}
						if((work <= 0 )||(address != -1))
						{
							shouldContinue = false;
						}
					}
					if(!shouldContinue)
					{
						break;
					}
				}
			});
	}
for(auto &t:pool)
	{
		t.join();
	}
	return address;
}










void parallelSearchData(std::vector<int> &vect,int item,int threads,int maxN)
{
	std::vector<double> vData;

	for(int i = 0; i<maxN;i++)
	{
		if(vect[threadedVectorFind(vect,item,threads)] != item)
		{
			std::cout << "ERROR! " << std::endl;
		}
    vData.push_back(timefunc([&,i](){threadedVectorFind(vect,item,threads);}));
	}
	std::cout << "For " << maxN  << " runs and size " << vect.size() << std::endl;
	std::cout << "The Average SEARCH time using " << threads << " threads was: " << vectorAverage(vData) << std::endl;	
	std::cout << "The Standard Deviation was: " << vectorStandardDev(vData) << std::endl << std::endl;
	vData.clear();
}



int serialPartition(std::vector<int> &vect,int start,int end)
{
	
	//int pivotValue = vect[start];
  int pivotPosition = start;

	int pivotValue;
	int middle = (start + end)/2;
	int a = vect[start];
	int b = vect[middle];
	int c = vect[end];
	while(true)
	{
		if(((a<b) && (b<c)) || ((c<b) && (b<a)))
		{
			pivotValue = vect[middle];
			break;
		}	
		if(((a<c) && (c<b)) || ((b<c) && (c<a)))
		{
			pivotValue = vect[end];
			break;
		}
		if(((b<a) && (a<c)) || ((c<a) && (a<b)))
		{
			pivotValue = vect[start];
			break;
		}
		pivotValue = vect[middle];
		break;
	}

	for(int pos = start + 1; pos <= end; pos++)
	{
		if(vect[pos] < pivotValue)
		{
			std::swap(vect[pivotPosition + 1],vect[pos]);
			std::swap(vect[pivotPosition],vect[pivotPosition + 1]);
			pivotPosition++;
		}
	}
	return pivotPosition;
}


void serialQuickSort(std::vector<int> &vect,int start, int end)
{
	if(start < end)
	{
		if((end - start) < 16)
		{
			std::sort(vect.begin()+start,vect.begin()+end);
			return;
		}
		int p = serialPartition(vect,start,end);
		serialQuickSort(vect,start,p-1);
		serialQuickSort(vect,p+1,end);
	}			
}



void serialTester(std::vector<int> &vect,int maxN)
{
	std::vector<double> vData;
	
	for(int i = 0;i<maxN-1;i++)
	{
		std::vector<int> dataCopy(vect);
    vData.push_back(timefunc([&,i](){serialQuickSort(dataCopy,0,dataCopy.size()-1);}));
	}
	vData.push_back(timefunc([&](){vectorSort(vect);}));
	std::cout << "For " << maxN  << " runs and size " << vect.size()  << std::endl;
	std::cout << "The Average SERIAL QUICKSORT time was: " << vectorAverage(vData) << std::endl;	
	std::cout << "The Standard Deviation was: " << vectorStandardDev(vData) << std::endl << std::endl;
	vData.clear();

}


void parallelQuickSort(std::vector<int> &vect,int start,int end)
{
	if(start < end)
	{
		if((end - start) < 16)
		{
			std::sort(vect.begin()+start,vect.begin()+end);
			return;
		}
		int p = serialPartition(vect,start,end);

		thread2.post(std::function<void(void)>([&](){
		parallelQuickSort(vect,start,p-1);
		}));

		thread2.post(std::function<void(void)>([&](){
		parallelQuickSort(vect,p+1,end);
		}));
	
	}		
}



void parallelQSort(std::vector<int> &vect,int threads)
{
	std::cout << vect.size() << " " << threads << std::endl;
 	thread2.post(std::function<void(void)>([&](){
	parallelQuickSort(vect,0,vect.size()-1);
	}));
	
	thread2.start();
	thread2.run();

}





int main()
{

	unsigned seed;
	seed = time(0);
	srand(seed);

	int nData = 50;


	std::vector<int> hundred;
	fillVector(hundred,100);
	int hundredVal = hundred[rand()%100];
	std::vector<int> hundredCopy(hundred);
	std::vector<int> hundredThreadedCopy(hundred);


	std::vector<int> oneK;
	fillVector(oneK,1000);
	int oneKVal = oneK[rand()%1000];
	std::vector<int> oneKCopy(oneK);
	std::vector<int> oneKThreadedCopy(oneK);

	std::vector<int> tenK;
	fillVector(tenK,10000);
	int tenKVal = tenK[rand()%10000];
	std::vector<int> tenKCopy(tenK);
	std::vector<int> tenKThreadedCopy(tenK);


	std::vector<int> hundredK;
	fillVector(hundredK,100000);
	int hundredKVal = hundredK[rand()%100000];
	std::vector<int> hundredKCopy(hundredK);
	std::vector<int> hundredKThreadedCopy(hundredK);


	std::vector<int> oneM;	
	fillVector(oneM,1000000);
	int oneMVal = oneM[rand()%1000000];
	std::vector<int> oneMCopy(oneM);	
	std::vector<int> oneMThreadedCopy(oneM);



	//std::cout << "before:" << std::endl;
	//for(int i =0;i<20;i++)
	//{	
	//  std::cout << "hundred: " << hundredCopy[i] << " oneK: " << oneKCopy[i] << " tenK: " << tenKCopy[i]  
	//  << " hundredK: " << hundredKCopy[i] << " oneM: "  << oneMCopy[i] << std::endl;
  //}



	stdStatsGiver(hundredCopy,nData,hundredVal);
	stdStatsGiver(oneKCopy,nData,oneKVal);
	stdStatsGiver(tenKCopy,nData,tenKVal);
	stdStatsGiver(hundredKCopy,nData,hundredKVal);
	stdStatsGiver(oneMCopy,nData,oneMVal);


	//std::cout << "after:" << std::endl;
	//for(int i =0;i<20;i++)
	//{	
	//  std::cout << "hundred: " << hundredCopy[i] << " oneK: " << oneKCopy[i] << " tenK: " << tenKCopy[i]  
	//  << " hundredK: " << hundredKCopy[i] << " oneM: "  << oneMCopy[i] << std::endl;
  //}

	//Now we are going to start with using a thread pool with linear search
	//First we make a copy of the data to be sorted


  // First we implement parallel search
	
	std::cout << "Begin new work \n" << std::endl;
	
	for(int i = 2;i<9;i++)
	{
		parallelSearchData(hundredThreadedCopy, hundredVal,i,nData);
		parallelSearchData(oneKThreadedCopy, oneKVal,i,nData);
		parallelSearchData(tenKThreadedCopy, tenKVal,i,nData);
		parallelSearchData(hundredKThreadedCopy, hundredKVal,i,nData);
		parallelSearchData(oneMThreadedCopy, oneMVal,i,nData);
	}


	// Half way there!
	// now make a serial quick sort

	std::cout << "before:" << std::endl;
	for(int i =0;i<20;i++)
	{	
	  std::cout << "hundred: " << hundredThreadedCopy[i] << " oneK: " << oneKThreadedCopy[i] << " tenK: " << tenKThreadedCopy[i]  
	  << " hundredK: " << hundredKThreadedCopy[i] << " oneM: "  << oneMThreadedCopy[i] << std::endl;
  }

/*	
	std::cout << "before:" << std::endl;
	for(int i =0;i<20;i++)
	{	
	  std::cout << "hundred: " << hundredThreadedCopy[i] << " oneK: " << oneKThreadedCopy[i] << " tenK: " << tenKThreadedCopy[i]  
	  << " hundredK: " << hundredKThreadedCopy[i] << " oneM: "  << oneMThreadedCopy[i] << std::endl;
  }

	serialTester(hundredThreadedCopy,nData);	
	serialTester(oneKThreadedCopy,nData);
	serialTester(tenKThreadedCopy,nData);
	serialTester(hundredKThreadedCopy,nData);
	serialTester(oneMThreadedCopy,nData);

	std::cout << "after:" << std::endl;
	for(int i =0;i<20;i++)
	{	
	  std::cout << "hundred: " << hundredThreadedCopy[i] << " oneK: " << oneKThreadedCopy[i] << " tenK: " << tenKThreadedCopy[i]  
	  << " hundredK: " << hundredKThreadedCopy[i] << " oneM: "  << oneMThreadedCopy[i] << std::endl;
  }
*/
	std::cout << "*******************  BEGIN MORE NEW WORK  ************************" << std::endl;
	// now do quick sort in parallel

	parallelQSort(hundredThreadedCopy,2);
	

	std::cout << "after:" << std::endl;
	for(int i =0;i<20;i++)
	{	
	  std::cout << "hundred: " << hundredThreadedCopy[i] << " oneK: " << oneKThreadedCopy[i] << " tenK: " << tenKThreadedCopy[i]  
	  << " hundredK: " << hundredKThreadedCopy[i] << " oneM: "  << oneMThreadedCopy[i] << std::endl;
  }


	std::cout << "Finished! " << std::endl;

	return 0;
}


