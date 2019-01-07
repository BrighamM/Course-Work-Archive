#include "unit.h"
#include "hastings.h"
#include <cmath>

float dist(int ar, int ac, int br, int bc)
{
  return sqrt((double)(br - ar) * (br - ar) + (bc - ac) * (bc - ac));
}

Unit::Unit()
{
  r = 0;
  c = 0;
  hp = 0;
  dir = up;
  rank = infantry;
  dead = false;
  playerName = "";
}

int Unit::getRow()
{
  return r;
}

int Unit::getCol()
{
  return c;
}

int Unit::getHp()
{
  return hp;
}

Dir Unit::getDir()
{
  return dir;
}

Rank Unit::getRank()
{
  return rank;
}

bool Unit::getDead()
{
  return dead;
}

string Unit::getPlayerName()
{
  return playerName;
}

void Unit::Turn(Dir newDir)
{
  dir = newDir;
}

void Unit::Move(int dist)
{
  switch(dir)
  {
    case up:
      r -= dist;
      break;

    case dn:
      r += dist;
      break;

    case lt:
      c -= dist;
      break;

    case rt:
      c += dist;
      break;

    case none:
      break;
	}
}

int Unit::Attack()
{
  int hits = 0;
  int d = 0;
  int rolls = hp;

  if (rank == crown || rank == knight)
  {
    rolls *= 2;
  }

  int tr = r;
  int tc = c;

  switch (dir)
  {
    case up:
      tr--;
      break;

    case dn:
      tr++;
      break;

    case rt:
      tc++;
      break;

    case lt:
      tc--;
      break;

    case none:
      break;
	}

  for (int i = 0; i < rolls; ++i)
  {
    d = rand() % 6;

    if (rank == archer && (d == 3 || d == 4))
    {
      hits++;
    }
    else if (d < 3)
    {
      hits++;
    }
	}

	//if I am an archer or infantry,
	//and there is only one of me,
	//and i rolled 1 hit,
	//then i am allowed to roll again
  if((rank == archer || rank == infantry) && hp == 1 && hits == 1)
  {
    hits += rand() % 2;
  }

	return hits;
}

void Unit::Suffer(int hits)
{
  if (rank == crown || rank == knight)
  {
    hits /= 2;
  }

  hp -= hits;

  if(hp <= 0)
  {
    dead = true;
	}
}
