/************************
* A#: A00364835
* Course: CS1400
* CS1400 Section: 1
* CS1405 Section: 11
* HW#: 14
***********************/

#include "ultron.h"

// Your ultron class inherits from the base unit class, this gives you access to the following public methods (as if
// they were declared inside of the ultron class itself).  Use them inside your functions below to make decisions.
//int getRow() : Gets the row coordinate of this unit (0 to ROWS - 1)
//int getCol() : Gets the column coordinate of this unit (0 to COLS - 1)
//int getHp() : Gets how much HP this unit has
//Dir getDir() : Gets the direction this unit is facing (up, dn, lt, rt, none)
//Rank getRank() : Gets the rank of this unit (infantry, archer, knight, crown)
//bool getDead() : If this unit is dead
//string getPlayerName() : Gets the name of the owner of this unit

ultron::ultron(Rank rank)
{
  // Initialize anything you would like
}

/*
 * Put unit on the board, inside the bounding box define by box min r,c and max r,c.
 * Don't put two units in the same place. Use getRank() to see the type of unit and the sitrep parameter if you want to
 * look at the game board.
 * Create, fill in, and return a Location object with a valid location where you want to place this unit.
 * 
 * Invalid unit placement will result in their death!
 */
Location ultron::Place(Box box, SitRep sitrep)
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

/*
 * Specify an action for this unit for this turn. Return an action which contains a single action for this unit (remember
 * that each unit is its own instance of your ultron class, this function will be called once for each unit each turn).
 * Remember to use your inherited member functions (getRank(), getDir(), getPlayerName(), etc.) to understand what unit
 * you are working with.
 *
 * Available actions:
 *
 * nothing: Have the unit do nothing (no need to populate anything else)
 *
 * turn: Turn the unit, you must also set the direction you want the unit to face
 * For example, to turn the unit to face right:
 * Action theAction;
 * theAction.action = turn;
 * theAction.dir = rt;
 *
 * fwd: Move the unit forward.  You must also specify the distance to move forward.  All units may move one space in the
 * direction they are facing, except knights, which may move up to 5 spaces.  Specify the distance as follows:
 * Action theAction;
 * theAction.action = fwd;
 * theAction.maxDist = 1;
 *
 * attack: Tell the unit to attack.  Most units (with the exception of archers) can only attack if they are facing an
 * enemy that is directly in front of them.
 * Archers can attack any unit that is within a 3x3 grid in front of the archer (see diagram below).  For archer units,
 * you must also specify the location where you would like them to shoot by filling in the archerRow and archerCol
 * variables inside the Action struct.
 *
 *     X X X
 *  A> X X X
 *     X X X
 *
 * SitRep Parameter: Useful information about the state of the game and path finding information for to enemy units
 * sitrep.board: Look at the entire game board. Each space contains a Thing which will tell you what is in that space.
 * sitrep.board[x][y].what: Get what is at a location (unit, space, rock)
 * sitrep.board[x][y].dir: Direction the unit at the location x,y is facing
 * sitrep.board[x][y].hp: How many HP the unit at the location x,y has
 * sitrep.board[x][y].playerName: Name of owner of unit at location x,y (might want to check if != getPlayerName())
 * sitrep.board[x][y].rank: Get what rank of unit is at location x,y
 * sitrep.anyOpenSpace: Give you a direction to an empty space where you could turn/move.
 * sitrep.nearestEnemy: Gives you the location of the nearest enemy unit
 * sitrep.nearestEnemy.dirFor: Gives you the direction you should go to reach the nearest enemy (will avoid obstacles for you!)
 * sitrep.nearestEnemyCrown: Gives you the location of the enemy crown
 * sitrep.nearestEnemyCrown.dirFor: Gives you the direction you should go to reach the nearest enemy crown (will avoid obstacles for you!)
 */
Action ultron::Recommendation(SitRep sitrep)
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
