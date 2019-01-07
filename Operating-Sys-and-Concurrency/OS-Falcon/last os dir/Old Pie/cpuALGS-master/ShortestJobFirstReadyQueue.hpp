#ifndef CS3100_SCHEDULER_SHORTEST_JOB_FIRST_R_Q_HPP
#define CS3100_SCHEDULER_SHORTEST_JOB_FIRST_R_Q_HPP

#include "ReadyQueue.hpp"
#include <queue>
#include <iostream>
namespace cs3100
{
  //class Simulation;

  class ShortestJobFirstReadyQueue : public ReadyQueue
  {
  public:
    //ShortestJobFirstReadyQueue();
    // Shortest Job First needs to be able to look inside current simulation
    void associateSimulator(Simulation* s) override;
    void add(int) override;
    int next() override;

  private:
    std::queue<int> queue;
    Simulation* simulator;
  };
}
#endif
