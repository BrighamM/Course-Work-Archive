#include "BrighamMichaelis.hpp"
#include <random>
#include <iostream>

lionheart::Placement lionheart::BrighamMichaelis::placeUnit(UnitType,
                                              StartBox const &box,
                                              SituationReport report)
{

	   for (int r = box.minRow; r < box.maxRow; ++r)
    for (int c = box.minCol; c < box.maxCol; ++c)
      if (report.things[r][c].type == SituationReport::SPACE) return {r, c};
  return {0, 0};
}

  lionheart::Action
lionheart::BrighamMichaelis::recommendAction(Unit const & u, SituationReport, Plan p)
{
 if (u.getType() == CROWN)
  {
    if (p.movesToEnemy() < 2)
    {
      return p.moveToEnemyCrown();
    }
    return wait();
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
}

lionheart::Blazon lionheart::BrighamMichaelis::getBlazon()
{
  /*Return your blazon here.  In case of conflicts preference will be given to
   * the students that have registered their blazons in class.*/
  return { Color::VERT, Color::GULES, Style::BEND, "Brigham Michaelis" };
}

