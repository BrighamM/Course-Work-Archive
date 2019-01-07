/************************
* A#: A00364835
* Course: CS1400
* CS1400 Section: 1
* CS1405 Section: 11
* HW#: 14
***********************/

#ifndef ULTRON_H
#define ULTRON_H

#include "unit.h"

class ultron : public Unit
{
public:
  ultron(Rank rank);

  Location Place(Box box, SitRep sitrep);
  Action Recommendation(SitRep sitrep);

private:
  // Add anything you would like
};


#endif // ULTRON_H

