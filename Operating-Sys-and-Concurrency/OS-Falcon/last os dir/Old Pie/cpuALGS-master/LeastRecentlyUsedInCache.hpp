#ifndef CS3100_SCHEDULER_LRUCACHE_HPP
#define CS3100_SCHEDULER_LRUCACHE_HPP

#include "CacheAlgorithm.hpp"
namespace cs3100
{

  class LRUInCache : public CacheAlgorithm
  {
  public:
    LRUInCache() 
	{
					cacheSize = 5;
			for(int i = 0;i<cacheSize;i++)
			{
				cache.push_back(-99);
				lru.push_back(false);
				//std::cout << cache[i] << ":"  <<  i  << std::endl;
			}
	}
	bool in(int input) override 
		{
			//std::cout<<"hello from mru:" << input <<std::endl;
			bool itsInHere = false;

			for(int i = 0;i<cacheSize;i++)
			{
				if(input == cache[i])
				{
					itsInHere = true;
					for(int j = 0;j<cacheSize;j++)
					{
						lru[j] = true;
					}
					lru[i] = false;
				}
			}

			if(!itsInHere)
			{
				load(input);
			}

			return itsInHere;
			 
		}


    void load(int input) override 
		{
			//std::cout << "hello from load: " << input << std::endl;
			for (int i = 0;i<cacheSize;i++)
			{
				if(cache[i] == -99)
				{
					cache[i] = input;
					for(int j = 0;j<cacheSize;j++)
					{
						lru[j] = true;
					}
					lru[i] = false;
					return;
				}
			}
			for(int i = 0;i<cacheSize;i++)
			{
				if(lru[i] == false)
				{
					cache[i] = input;
					return;
				}
			}
			return;
		}


			int cacheSize;
		std::vector<int> cache;
		std::vector<bool> lru;
  };
}

#endif
