#ifndef THREAD_POOL
#define THREAD_POOL

#include <condition_variable>
#include <mutex>
#include "TSQ.h"
#include <atomic>
#include <thread>
#include <iostream>

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
			f();
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




#endif
