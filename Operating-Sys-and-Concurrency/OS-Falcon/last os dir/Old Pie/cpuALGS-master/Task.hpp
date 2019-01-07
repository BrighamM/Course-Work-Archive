#ifndef CS3100_SCHEDULER_TASK_HPP
#define CS3100_SCHEDULER_TASK_HPP

#include <iostream>
#include <vector>
#include <numeric>
namespace cs3100
{


  struct Task
  {
    const float duration;
    float progress;
    float completionTime;
    const int device;
    enum Type
    {
      CPU,
      IO
    };
    const Type type;
    bool isDone() 
		{
			 return progress >= duration; 
		}
    Task(float dur, int dev, Type t)
      : duration(dur),progress(0.0f),completionTime(-1.0f),device(dev), type(t)
    {

    }
    Task(Task const& o) = default;
  };

  struct Job
  {
    Job(float, int, int);
    const float creationTime;
    unsigned int cur;
    std::vector<Task> tasks;

		float getFinalCompletionTime()
		{
			return tasks[tasks.size()-1].completionTime;
		}

		float getIOAverage()
		{
			std::vector<Task> ioTimeVector;
			for(auto&& e:tasks)
			{
				if(e.type == Task::IO)
				{
					ioTimeVector.push_back(e);
				}				
			}
			if(ioTimeVector.empty())
			{
				return -0.0;
			}
			std::vector<float> diffs;

			for(unsigned int i = 1; i<(ioTimeVector.size() -1);i++)
			{
				diffs.push_back(ioTimeVector[i].completionTime - ioTimeVector[i-1].completionTime);
			}
			if(diffs.empty())
			{
				return -0.0;
			}
			
			return std::accumulate(diffs.begin(), diffs.end(),0.0)/diffs.size();

		}
  };
}

#endif
