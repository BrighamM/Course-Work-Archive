
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

std::atomic<int> qSortWork(0);

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
			return q.empty();
		}

	private: 
		std::mutex m;
		std::queue<T> q;
};
TSQ<std::function<void(void)>> parallelQ;


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
	std::cout << "The Average STD::SEARCH time was: " << vectorAverage(vData) << std::endl;	
	std::cout << "The Standard Deviation was: " << vectorStandardDev(vData) << std::endl << std::endl;
	vData.clear();

	for(int i = 0; i<maxN-1;i++)
	{
		std::vector<int> vCData(svec);
    vData.push_back(timefunc([&,i](){vectorSort(vCData);}));
	}
	vData.push_back(timefunc([&](){vectorSort(svec);}));
	std::cout << "For " << maxN  << " runs and size " << svec.size()  << std::endl;
	std::cout << "The Average STD::SORT time was: " << vectorAverage(vData) << std::endl;	
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
	int pivotValue = vect[start];
  int pivotPosition = start;
/*
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
			//pivotPosition = middle;
			break;
		}	
		if(((a<c) && (c<b)) || ((b<c) && (c<a)))
		{
			pivotValue = vect[end];
			//pivotPosition = end;
			break;
		}
		if(((b<a) && (a<c)) || ((c<a) && (a<b)))
		{
			pivotValue = vect[start];
			//pivotPosition = start;
			break;
		}
		pivotValue = vect[middle];
		//pivotPosition = middle;
		break;
	}
	*/
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




void parallelQuickSort(std::vector<int> &vect,int start, int end)
{
	if(start < end)
	{
		int p = serialPartition(vect,start,end);
		parallelQ.enqueue(std::function<void(void)>([&,p,start](){
		parallelQuickSort(vect,start,p-1);
		}));
		qSortWork++;
		parallelQ.enqueue(std::function<void(void)>([&,p,end](){
		parallelQuickSort(vect,p+1,end);
		}));
		qSortWork++;
	}			
}
void parallelQSort(std::vector<int> &vect,int threads)
{
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
}




int main()
{

	unsigned seed;
	seed = time(0);
	srand(seed);

	int nData = 10;


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


	for(int i = 2;i<9;i++)
	{
		parallelSearchData(hundredThreadedCopy, hundredVal,i,nData);
		parallelSearchData(oneKThreadedCopy, oneKVal,i,nData);
		parallelSearchData(tenKThreadedCopy, tenKVal,i,nData);
		parallelSearchData(hundredKThreadedCopy, hundredKVal,i,nData);
		parallelSearchData(oneMThreadedCopy, oneMVal,i,nData);
	}


		
	std::cout << "Partial printing of unsorted vectors prior to Parallel Quick Sort:" << std::endl;
	for(int i =0;i<20;i++)
	{	
	  std::cout << "hundred: " << hundredThreadedCopy[i] << " oneK: " << oneKThreadedCopy[i] << " tenK: " << tenKThreadedCopy[i]  
	  << " hundredK: " << hundredKThreadedCopy[i] << " oneM: "  << oneMThreadedCopy[i] << std::endl;
  }

/*
	serialTester(hundredThreadedCopy,nData);	
	serialTester(oneKThreadedCopy,nData);
	serialTester(tenKThreadedCopy,nData);
	serialTester(hundredKThreadedCopy,nData);
	serialTester(oneMThreadedCopy,nData);
*/


	int ijk = 4;

			
	//	std::cout << timefunc([&,ijk](){parallelQSort(hundredThreadedCopy,ijk);}) << std::endl;
	parallelQSort(hundredThreadedCopy,ijk);
	//	std::cout << timefunc([&,ijk](){parallelQSort(oneKThreadedCopy,ijk);}) << std::endl;
	parallelQSort(oneKThreadedCopy,ijk);		
	//	std::cout << timefunc([&,ijk](){parallelQSort(tenKThreadedCopy,ijk);}) << std::endl;
	parallelQSort(tenKThreadedCopy,ijk);
	//	std::cout << timefunc([&,ijk](){parallelQSort(hundredKThreadedCopy,ijk);}) << std::endl;
	parallelQSort(hundredKThreadedCopy,ijk);
	//	std::cout << timefunc([&,ijk](){parallelQSort(oneMThreadedCopy,ijk);}) << std::endl;
	parallelQSort(oneMThreadedCopy,ijk);



	std::cout << "\nPartial printing of sorted vectors after Parallel Quick sort: " << std::endl;
	for(int i =0;i<20;i++)
	{	
	  std::cout << "hundred: " << hundredThreadedCopy[i] << " oneK: " << oneKThreadedCopy[i] << " tenK: " << tenKThreadedCopy[i]  
	  << " hundredK: " << hundredKThreadedCopy[i] << " oneM: "  << oneMThreadedCopy[i] << std::endl;
  }





	std::cout << "Finished! " << std::endl;

	return 0;
}


