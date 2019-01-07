#ifndef LIONHEART_H
#define LIONHEART_H
#include <sstream>
#include "playerInfo.h"

using namespace std;

#define INFILE          "map.in"
#define TINYMAP         0
#define DOTS            0
#define ANSI            1
#define AUTOTOURNEY     0
#define AUTONUMMATCHES  100
#define MAXTURNS        200
#define INFANTRYHP      10
#define ARCHERHP        10
#define KNIGHTHP        5
#define CROWNHP         1
#define NUM             60
#define NUMKNIGHTS      12
#define NUMARCHERS      12
#define HORSESPEED      5
#define ROWS 30
#define COLS 30

struct UnitCounts
{
  int crowns;
  int knights;
  int archers;
  int infantry;
};

class Hastings
{
public:
  Hastings();
  void play();

private:
  void unit2thing(Unit *u, int r, int c);
  void makeB(Unit *u[NUM]);
  bool nextToBarrier(Unit *u);
  bool localSearch(Dir map[ROWS][COLS], Dir map2[ROWS][COLS], int r, int c);
  Dir pathDirFor(int sr, int sc, int er, int ec);
  float getDist(int r, int c, int tr, int tc);
  Location getNearestEnemyCrown(Unit *u[], int m);
  Location getNearestEnemy(Unit *u[], int m);
  Dir manhattenDirFor(Unit *u, int tr, int tc);
  Dir anyDir(Unit *u);
  SitRep makeSitRep(Unit *u[NUM], int m);
  int totalHp(Unit *u[], int m);
  void display(Unit* u[]);
  void readMap();
  void printNameList();
  bool checksOut(string name);
  Unit* newUnit(string player, Rank rank);
  void updateB(Unit* u);
  bool readScenario(UnitCounts counts[], string sFile);
  bool setUpBoard(Unit* u[NUM], string sFile);
  void validatePlacement(Unit* u[NUM], Box startBox, Location loc, int unitCounter);
  int clear(Unit *u[], int m, int dist);
  void arrowSuffer(Unit *u[], int m, int ar, int ac, int hits);
  void makeSuffer(Unit *u[], int m, int hits);
  void autoTourney(Unit *u[NUM]);
  bool oneLeft(Unit *u[NUM]);
  void doTurn(Unit *u[NUM]);

  Thing b[ROWS][COLS];
  char c[ROWS][COLS];
  int numplayers;
  int turnNum;
  string players[4];
  string color[4];
  Box startBox[4];
  stringstream sout;
};
#endif
