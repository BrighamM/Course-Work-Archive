#include "ApproximateShortestJobFirstReadyQueue.hpp"
#include "Simulation.hpp"
#include <stdexcept>
namespace cs3100
{
	void ApproximateShortestJobFirstReadyQueue::associateSimulator(Simulation* s)
	{
		simulator = s;
		//int temp = 456;
		//temp = simulator->idleCpu;
		//std::cout<< "KINGME3:" << temp << std::endl;
	
	}

  void ApproximateShortestJobFirstReadyQueue::add(int x)
  {
		queue.push(x); 
  }

  int ApproximateShortestJobFirstReadyQueue::next()
  {
		if(queue.empty()) return -1;
		auto result = queue.front();
		queue.pop();
		return result;  
  }
}
