#ifndef CS3100_SCHEDULER_SECONDCHANCE_HPP
#define CS3100_SCHEDULER_SECONDCHANCE_HPP

#include "CacheAlgorithm.hpp"
namespace cs3100
{

  class SecondChanceCache : public CacheAlgorithm
  {
  public:
    SecondChanceCache() 
		{
			cacheSize = 5;
			for(int i = 0;i<cacheSize;i++)
			{
				cache.push_back(-99);
				marked.push_back(false);
			}

		}
    bool in(int input) override 
		{ 
			bool itsInHere = false;
			
			for(int i = 0;i<cacheSize;i++)
			{
				if(cache[i] == input)
				{
					itsInHere = true;
					marked[i] = true;
					return itsInHere;
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
			int index = 0;
			for(int i = 0; i< ((cacheSize*2)-1); i++)
			{
				if(!marked[index])
				{

					cache[i] = input;


				}
				if(marked[index])
				{
					marked[index] = false;
				}
				

				
			}

		
		}


		int cacheSize;
		std::vector<int> cache;
		std::vector<bool> marked;
  };
}

#endif
