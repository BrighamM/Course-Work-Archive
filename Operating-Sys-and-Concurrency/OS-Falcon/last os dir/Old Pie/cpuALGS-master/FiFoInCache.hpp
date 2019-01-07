#ifndef CS3100_SCHEDULER_FIFO_HPP
#define CS3100_SCHEDULER_FIFO_HPP

#include "CacheAlgorithm.hpp"
namespace cs3100
{

  class FifoInCache : public CacheAlgorithm
  {
  public:
    FifoInCache() 
		{
			cacheSize = 5;
			for(int i = 0;i<cacheSize;i++)
			{
				cache.push_back(-99);
				fi.push_back(false);
			}

		}
    bool in(int input) override 
		{ 
			bool itsInHere = false;

			for(int i = 0;i<cacheSize;i++)
			{
				if(input == cache[i])
				{
					itsInHere = true;
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
			bool empty = false;

			for(int i = 0;i<cacheSize;i++)
			{
				if(cache[i] == -99)
				{
					empty = true;					
				}
			}

			if(empty)
			{
				fi[0] = true;
				for(int i = 0;i<cacheSize;i++)
				{	
					if(cache[i] == -99)
					{
						cache[i] = input;
						return;					
					}
				}				
			}
			
		
			int index = 0;
			for(int i = 0;i<cacheSize;i++)
			{
				if(fi[i])
				{
					cache[i] = input;
					index = i;
					fi[i] = false;
										
				}
			}

			index = index + 1;
			index = index%cacheSize;
			return;


		}

		int cacheSize;
		std::vector<int> cache;
		std::vector<bool> fi;
		
		

  };
}

#endif
