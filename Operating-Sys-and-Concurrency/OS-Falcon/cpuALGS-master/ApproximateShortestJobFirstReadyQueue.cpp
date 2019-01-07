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
		float temp = 0;
		for(int i = 0;i<(int)simulator->jobs[x].tasks.size();i++)
		{
			if(simulator->jobs[x].tasks[i].type == 0)
			{
				temp += simulator->jobs[x].tasks[i].duration;								
			}
		}
		Epoint newthing(x,temp);

		queue.push(newthing); 
  }

  int ApproximateShortestJobFirstReadyQueue::next()
  {
		if(queue.empty()) return -1;
		auto result = queue.top().index;
		queue.pop();
		return result;  
  }
}
