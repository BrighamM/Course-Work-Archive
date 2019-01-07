#include "AlwaysInCache.hpp"
#include "MostRecentlyUsedInCache.hpp"
#include "LeastRecentlyUsedInCache.hpp"
#include "FiFoInCache.hpp"
#include "SecondChanceInCache.hpp"
#include "FifoReadyQueue.hpp"
#include "ShortestJobFirstReadyQueue.hpp"
#include "ApproximateShortestJobFirstReadyQueue.hpp"
#include "Simulation.hpp"
#include <iostream>
#include <limits>

namespace
{
  void report(cs3100::Simulation& s)
  {
    /*TODO create a report based on the results in s*/
    std::cout << "Efficiency : " << s.getEfficiency() << std::endl;
    std::cout << "Task\tLatency\tResponseTime" << std::endl;
    for (size_t i = 0; i < s.getJobs(); ++i)
    {
      std::cout << i << "\t" << s.rawLatency(i) << "\t" << s.rawResponseTime(i)<< std::endl;
    }
  }

  template <typename ReadyType, typename CacheType>
  void runSimulation(cs3100::SimulationParameters const& p)
  {
		// here we instantiate a simulator with the scheduling algorithm and 
		// the respective parameters
    cs3100::Simulation s(p, std::make_unique<ReadyType>(), std::make_unique<CacheType>());
    // now we call the sims run method
		s.run();
    report(s);
  }
}

int main()
{

	// MOST RECENTLY USED CACHE ALGORITHM
	std::cout << "MOST RECENTLY USED CACHE ALGORITHM" << std::endl;
  cs3100::SimulationParameters fifo;
  fifo.cpus = 4;
  fifo.devices = 2;
  fifo.cacheSize = 5;
  fifo.contextSwitchCost = 0.1f;
  fifo.cacheMissCost = 5.0f;
  fifo.maximumTimeSlice = std::numeric_limits<float>::max();
  fifo.jobs = 10;
  fifo.meanTimeBetweenJobs = 10.0f;
  fifo.stddevTimeBetweenJobs = 2.0f;
  runSimulation<cs3100::FifoReadyQueue, cs3100::MRUInCache>(fifo);



	// LEAST RECENTLY USED CACHE ALGORITHM	
	std::cout << "LEAST RECENTLY USED CACHE ALGORITHM" << std::endl;
  cs3100::SimulationParameters roundRobin;
  roundRobin.cpus = 4;
  roundRobin.devices = 2;
  roundRobin.cacheSize = 5;
  roundRobin.contextSwitchCost = 0.1f;
  roundRobin.cacheMissCost = 5.0f;
  roundRobin.maximumTimeSlice = std::numeric_limits<float>::max();
  roundRobin.jobs = 10;
  roundRobin.meanTimeBetweenJobs = 10.0f;
  roundRobin.stddevTimeBetweenJobs = 2.0f;
  runSimulation<cs3100::FifoReadyQueue, cs3100::LRUInCache>(roundRobin);


	// FIRST IN FIRST OUT CACHE ALGORITHM
	std::cout << "FIRST IN FIRST OUT CACHE ALGORITHM" << std::endl;
  cs3100::SimulationParameters shortestJF;
  shortestJF.cpus = 4;
  shortestJF.devices = 2;
  shortestJF.cacheSize = 5;
  shortestJF.contextSwitchCost = 0.1f;
  shortestJF.cacheMissCost = 5.0f;
  shortestJF.maximumTimeSlice = std::numeric_limits<float>::max();
  shortestJF.jobs = 10;
  shortestJF.meanTimeBetweenJobs = 10.0f;
  shortestJF.stddevTimeBetweenJobs = 2.0f;
  runSimulation<cs3100::FifoReadyQueue, cs3100::FifoInCache>(shortestJF);



	// SECOND CHANCE CACHE ALGORITHM
	std::cout << "SECOND CHANCE CACHE ALGORITHM" << std::endl;
  cs3100::SimulationParameters appxSJF;
  appxSJF.cpus = 4;
  appxSJF.devices = 2;
  appxSJF.cacheSize = 5;
  appxSJF.contextSwitchCost = 0.1f;
  appxSJF.cacheMissCost = 5.0f;
  appxSJF.maximumTimeSlice = std::numeric_limits<float>::max();
  appxSJF.jobs = 10;
  appxSJF.meanTimeBetweenJobs = 10.0f;
  appxSJF.stddevTimeBetweenJobs = 2.0f;
  runSimulation<cs3100::FifoReadyQueue, cs3100::SecondChanceCache>(appxSJF);


	return 0;
}
