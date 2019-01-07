#ifndef _JARVIS_H
#define _JARVIS_H

#include "unit.h"

class jarvis : public Unit
{
public:
  jarvis(Rank rank)
  {

  }

  Location Place(Box box, SitRep sitrep)
  {
    Location toPlace;

    bool spotFound = false;
    for (int i = box.minr; i <= box.maxr && !spotFound; ++i) 
    {
      for (int j = box.minc; j <= box.maxc && !spotFound; ++j) 
      {
        // Finds a sport within the starting box that in unoccupied
        if (sitrep.board[i][j].what == space)
        {
          // Set the location where we want to place the unit
          toPlace.r = i;
          toPlace.c = j;
          toPlace.dirFor = up; // Have the unit face up - just for fun

          spotFound = true;
        }
      }
    }

    // Return the populated location where you want to place the unit
    return toPlace;
  }

  Action Recommendation(SitRep sitrep)
  {
    Action theAction;

    // Make all the units spin around aimlessly
    theAction.action = turn;

    switch (getDir())
    {
      case lt:
        theAction.dir = up;
        break;
      case up:
        theAction.dir = rt;
        break;
      case rt:
        theAction.dir = dn;
        break;
      case dn:
        theAction.dir = lt;
        break;
    }

    return theAction;
  }
};


#endif // _JARVIS_H
