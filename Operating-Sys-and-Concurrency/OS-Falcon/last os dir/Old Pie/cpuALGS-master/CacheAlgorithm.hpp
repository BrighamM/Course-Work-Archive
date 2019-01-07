#ifndef CS3100_SCHEDULER_CACHE_ALGORITHM_HPP
#define CS3100_SCHEDULER_CACHE_ALGORITHM_HPP
#include <iostream>
#include <string>
#include <vector>
namespace cs3100
{
  class CacheAlgorithm
  {
  public:
    CacheAlgorithm(){};
    virtual bool in(int) = 0;
    virtual void load(int) = 0;
  };
}
#endif
