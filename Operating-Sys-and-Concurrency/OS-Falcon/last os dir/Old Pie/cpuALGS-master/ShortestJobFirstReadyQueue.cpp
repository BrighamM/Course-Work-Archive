#include "ShortestJobFirstReadyQueue.hpp"
#include "Simulation.hpp"
#include <stdexcept>
namespace cs3100
{

	void ShortestJobFirstReadyQueue::associateSimulator(Simulation* s)
	{
		simulator = s;
		//int temp = 456;
		//temp = simulator->idleCpu;
		//std::cout<< "KING ME2:" << temp << std::endl;
		//std::cin.ignore();
	}

  void ShortestJobFirstReadyQueue::add(int x)
  {
		queue.push(x);
  }

  int ShortestJobFirstReadyQueue::next()
  {
		if(queue.empty()) return -1;
		auto result = queue.front();
		queue.pop();
		return result;

  }
}
