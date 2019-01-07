#include "BrighamMichaelis.hpp"
#include <random>
#include <iostream>

lionheart::Placement lionheart::BrighamMichaelis::placeUnit(UnitType,
                                              StartBox const &box,
                                              SituationReport report)
{
  /*Fill this out with instructions on how to place your initial units.  Without
   * changes your units will fill the starting box from top left to bottom right
   * in the order constructed.*/
	 //persistance!!!!
  for (int r = box.minRow; r < box.maxRow; ++r)
    for (int c = box.minCol; c < box.maxCol; ++c)
      if (report.things[r][c].type == SituationReport::SPACE)
        return { r, c };
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

