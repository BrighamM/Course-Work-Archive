#ifndef LIONHEART_BRIGHAM_MICHAELIS
#define LIONHEART_BRIGHAM_MICHAELIS
#include "Player.hpp"

namespace lionheart
{
/*The : public Player bit allows this code to interact with the framework code
 * provided.  If your class file is Name.hpp the class needs to be named Name or
 * the framework code will not be able to find and add the player to
 * tournaments.*/
  class BrighamMichaelis : public Player
  {
  public:
		BrighamMichaelis():id(0),facingEast(false),turns(0),
		outerTurns(0),bloodlust(false),deathcount(0),kingMoving(0),kingIdle(0)
		{

		}
    Placement placeUnit(UnitType, StartBox const& box, SituationReport report);
    Action recommendAction(Unit const &, SituationReport, Plan);
    Blazon getBlazon();

	private:
		int id;
		bool facingEast;
		int turns;
		int outerTurns;
		bool bloodlust;
		int deathcount;
		int kingMoving;
		int kingIdle;
  };
}
#endif
