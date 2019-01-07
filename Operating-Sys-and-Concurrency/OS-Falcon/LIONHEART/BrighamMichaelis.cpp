#include "BrighamMichaelis.hpp"
#include <random>
#include <iostream>

lionheart::Placement lionheart::BrighamMichaelis::placeUnit(UnitType,
                                              StartBox const &box,
                                              SituationReport report)
{
facingEast = (box.minCol < static_cast<int>(report.things[0].size() / 2));
  
  id++;
  if (id > 30)
    id = 1; // resets id for each new game
  if (facingEast)
  {

    switch (id)
    {
    // CROWN
    case 1:
      return { 14, 4 };
    // KNIGHTS
    case 2:
      return { 11, 4 };
    case 3:
      return { 14, 6 };
    case 4:
      return { 18, 4 };
    case 5:
      return { 15, 6 };
    case 6:
      return { 12, 4 };
    case 7:
      return { 17, 4 };
    // ARCHERS
    case 8:
      return { 11, 3 };
    case 9:
      return { 11, 5 };
    case 10:
      return { 13, 7 };
    case 11:
      return { 12, 7 };
    case 12:
      return { 17, 7 };
    case 13:
      return { 16, 7 };
    case 14:
      return { 18, 3 };
    case 15:
      return { 18, 5 };
    // INFANTRY
    case 16:
      return { 10, 3 };
    case 17:
      return { 10, 5 };
    case 18:
      return { 10, 4 };
    case 19:
      return { 19, 3 };
    case 20:
      return { 19, 5 };
    case 21:
      return { 19, 4 };
    case 22:
      return { 12, 3 };
    case 23:
      return { 12, 5 };

    case 24:
    {

      return { 13, 6 };
    }
    case 25:
      return { 14, 7 };
    case 26:
      return { 15, 7 };
    case 27:
      return { 16, 6 };
    case 28:
      return { 17, 5 };
    case 29:
    {

      return { 17, 3 };
    }
    case 30:
    {

      return { 13, 3 };
    }
    }
  }
  else
  {

    switch (id)
    {
    // CROWN
    case 1:
      return { 14, 25 };
    // KNIGHTS
    case 2:
      return { 11, 25 };
    case 3:
      return { 14, 22 };
    case 4:
      return { 18, 25 };
    case 5:
      return { 15, 22 };
    case 6:
      return { 12, 25 };
    case 7:
      return { 17, 25 };
    // ARCHERS
    case 8:
      return { 11, 24 };
    case 9:
      return { 11, 26 };
    case 10:
      return { 13, 22 };
    case 11:
      return { 12, 22 };
    case 12:
      return { 17, 22 };
    case 13:
      return { 16, 22 };
    case 14:
      return { 18, 26 };
    case 15:
      return { 18, 24 };
    // INFANTRY
    case 16:
      return { 10, 24 };
    case 17:
      return { 10, 26 };
    case 18:
      return { 10, 25 };
    case 19:
      return { 19, 24 };
    case 20:
      return { 19, 26 };
    case 21:
      return { 19, 25 };
    case 22:
      return { 12, 26 };
    case 23:
      return { 12, 24 };

    case 24:
      return { 13, 23 };
    case 25:
      return { 14, 23 };
    case 26:
      return { 15, 23 };
    case 27:
      return { 16, 23 };
    case 28:
      return { 17, 26 };
    case 29:
      return { 17, 24 };
    case 30:
      return { 13, 26 };
    }
  }
  return { 0, 0 };
}

  lionheart::Action
lionheart::BrighamMichaelis::recommendAction(Unit const & u, SituationReport, Plan p)
{
  /*Fill this out with the behavior you want for your units.  Without changes
   * your units will just wait to be defeated.  Feel free to look at the other provided players for ideas on how to get certain behavior*/
  
		static int turns = 0;
		turns++;
		//static int stuck_turns = 0;

	if (u.getType() == CROWN)
  {
    if (p.movesToEnemy() < 2)
    {
      static std::random_device rd;
      static std::mt19937 engine(rd());
      return move(5);
    }
		if(turns%50 == 0)
		{
			return move(1);

		}

		return turn((Direction)(turns%4));
    //return wait();
  }


  if (u.getType() == KNIGHT)
  {
    if (p.hasAttack())
    {
      return p.attackEnemy();
    }		
    return p.moveToEnemyCrown();
  }

	return p.attackEnemy();
	if (u.getType() == ARCHER)
  {
      if (p.hasAttack())
      {
        return p.attackEnemy();
      }

			
			return p.moveToEnemyCrown();

  }
  if (u.getType() == INFANTRY)
  {

		
      if (p.hasAttack())
      {
        return p.attackEnemy();
      }

			
			return p.moveToEnemyCrown();
  }
	return p.moveToAllyCrown();
}

lionheart::Blazon lionheart::BrighamMichaelis::getBlazon()
{
  /*Return your blazon here.  In case of conflicts preference will be given to
   * the students that have registered their blazons in class.*/
  return { Color::VERT, Color::GULES, Style::BEND, "Brigham Michaelis" };
}

