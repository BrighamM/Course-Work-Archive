#include "FifoReadyQueue.hpp"
#include "Simulation.hpp"
namespace cs3100
{

	void FifoReadyQueue::associateSimulator(Simulation* s)
	{
		simulator = s;
		//int temp = 0;
		//temp = simulator->idleCpu;
		//std::cout << "KING ME!" << temp  << std::endl;
		//std::cin.ignore();
	}

  void FifoReadyQueue::add(int x) 
	{
		 queue.push(x); 
	}

  int FifoReadyQueue::next()
  {
    if (queue.empty()) return -1;
    auto result = queue.front();
    queue.pop();
    return result;
  }
}
