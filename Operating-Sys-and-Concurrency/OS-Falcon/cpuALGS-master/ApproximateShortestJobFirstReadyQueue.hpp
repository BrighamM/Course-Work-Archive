#ifndef DDDFFF
#define DDDFFF

#include "ReadyQueue.hpp"
#include <queue>
#include <iostream>
#include <vector>
namespace cs3100
{
 // class Simulation;

 struct Epoint
 {
	 public:
	 int index;
	 float time;
	 Epoint(int i, float t) : index(i),time(t){}		
 };
 struct EpointCompare
 {
	 bool operator()(const Epoint &t1,const Epoint&t2) const
	 {
		 float t1val = t1.time;
		 float t2val = t2.time;
		 return t1val > t2val;
	 }

 };

  class ApproximateShortestJobFirstReadyQueue : public ReadyQueue
  {
   // ApproximateShortestJobFirstReadyQueue();
    // Approximate Shortest Job First needs to be able to look inside current
    // simulation
    void associateSimulator(Simulation* s) override;

    void add(int) override;
    int next() override;

  private:
    std::priority_queue<Epoint,std::vector<Epoint>,EpointCompare> queue;
    Simulation* simulator;
  };
}

#endif
