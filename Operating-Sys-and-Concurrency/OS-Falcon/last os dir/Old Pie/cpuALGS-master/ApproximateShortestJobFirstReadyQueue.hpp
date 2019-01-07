#ifndef DDDFFF
#define DDDFFF

#include "ReadyQueue.hpp"
#include <queue>
#include <iostream>
namespace cs3100
{
 // class Simulation;

  class ApproximateShortestJobFirstReadyQueue : public ReadyQueue
  {
   // ApproximateShortestJobFirstReadyQueue();
    // Approximate Shortest Job First needs to be able to look inside current
    // simulation
    void associateSimulator(Simulation* s) override;

    void add(int) override;
    int next() override;

  private:
    std::queue<int> queue;
    Simulation* simulator;
  };
}

#endif
