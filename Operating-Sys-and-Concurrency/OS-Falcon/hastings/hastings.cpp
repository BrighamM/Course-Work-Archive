#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctime>
#include <string>
#include "hastings.h"
#include "unit.h"

Hastings::Hastings()
{

}

void Hastings::play()
{
  Unit* u[NUM];
  char line[1024];
  bool done = false;
  turnNum = 0;

#ifdef JARVIS
  srand(42);
#else
  srand(time(NULL));
#endif

  for (int i = 0; i < NUM; i++)
  {
    u[i] = NULL;
  }

  // if running an auto tourney, just do that and quit
  if (AUTOTOURNEY)
  {
    autoTourney(u);
    return;
  }

  // set up the board
#ifdef JARVIS
  if (!setUpBoard(u, "scenario.in"))
    return;
#else
  if (!setUpBoard(u, "finalBattle.in"))
    return;
#endif

  display(u);
  cin.getline(line, 1023);
  cout << sout.str();
  sout.str("");

  while (!done)
  {
    // do a turn
    ++turnNum;
    doTurn(u);
    display(u);


#ifndef JARVIS
    cin.getline(line, 1023);
#endif
    cout << sout.str();
    sout.str("");

    if (line[0] == 'q')
    {
      done = true;
    }

    if (oneLeft(u))
    {
      done = true;
    }

    if (turnNum > MAXTURNS)
    {
      done = true;
    }
  }
}

void Hastings::unit2thing(Unit *u, int r, int c){
  if(!u){b[r][c].what=space; return;}
  if(u->getDead()){b[r][c].what=space; return;}
  b[r][c].what = unit;
  b[r][c].rank = u->getRank();
  b[r][c].playerName = u->getPlayerName();
  b[r][c].dir = u->getDir();
  b[r][c].hp = u->getHp();
}

void Hastings::makeB(Unit *u[NUM]){
  int i,j;
  for(i=0;i<ROWS;++i){
    for(j=0;j<COLS;++j){
      b[i][j].what=space;
      if(c[i][j]=='X')b[i][j].what = rock;
    }
  }

  for(i=0;i<NUM;++i){
    if(u[i])unit2thing(u[i],u[i]->getRow(),u[i]->getCol());
  }
}

bool Hastings::nextToBarrier(Unit *u){
  int r,c;
  r=u->getRow();
  c=u->getCol();
  if(r-1>0     && c-1>0     && b[r-1][c-1].what == rock)return true;
  if(r-1>0                  && b[r-1][c  ].what == rock)return true;
  if(r-1>0     && c+1<=COLS && b[r-1][c+1].what == rock)return true;
  if(             c-1>0     && b[r  ][c-1].what == rock)return true;
  if(             c+1<=COLS && b[r  ][c+1].what == rock)return true;
  if(r+1<=ROWS && c-1>0     && b[r+1][c-1].what == rock)return true;
  if(r+1<=ROWS              && b[r+1][c  ].what == rock)return true;
  if(r+1<=ROWS && c+1<=COLS && b[r+1][c+1].what == rock)return true;
  return false;
}

bool Hastings::localSearch(Dir map[ROWS][COLS], Dir map2[ROWS][COLS],int r, int c){
  if(map[r][c]!=none)return false;
  if(b[r][c].what==rock)return false;

  if(r-1>=0  &&map2[r-1][c  ]!=none){map[r][c]=up;return true;}
  if(c+1<COLS&&map2[r  ][c+1]!=none){map[r][c]=rt;return true;}
  if(r+1<ROWS&&map2[r+1][c  ]!=none){map[r][c]=dn;return true;}
  if(c-1>=0  &&map2[r  ][c-1]!=none){map[r][c]=lt;return true;}

  return false;
}



Dir Hastings::pathDirFor(int sr, int sc, int er, int ec){
  Dir map[ROWS][COLS],map2[ROWS][COLS];

  int i,j;
  bool changes=true;

  for(i=0;i<ROWS;++i){
    for(j=0;j<COLS;++j){
      map[i][j]=none;
      map2[i][j]=none;
    }
  }
  map[er][ec]=rt;
  map2[er][ec]=rt;


  while(changes){
    changes=false;

    for(i=0;i<ROWS;++i){
      for(j=0;j<COLS;++j){
        if(localSearch(map,map2,i,j))changes=true;
      }
    }
    for(i=0;i<ROWS;++i){
      for(j=0;j<COLS;++j){
        map2[i][j]=map[i][j];
      }
    }
  }
  return map[sr][sc];
}


float Hastings::getDist(int r,int c,int tr,int tc){
  return sqrt((double)(tr-r)*(tr-r)+(tc-c)*(tc-c));
}

Location Hastings::getNearestEnemyCrown(Unit *u[], int m){
  int r,c; 
  string playerName;
  Location l;
  l.r = 0;
  l.c = 0;
  l.dirFor = none;

  r = u[m]->getRow();
  c = u[m]->getCol();
  playerName = u[m]->getPlayerName();

  for(int i = 0; i < NUM; ++i)
  {
    if(i != m && u[i] && !u[i]->getDead() && u[i]->getPlayerName() != playerName && u[i]->getRank() == crown)
    {
      l.r = u[i]->getRow();
      l.c = u[i]->getCol();
      l.dirFor = pathDirFor(r,c,l.r,l.c);
      break;
    }
  }

  return l;
}

Location Hastings::getNearestEnemy(Unit *u[], int m){
  int r,c;
  int tr,tc;
  string playerName;
  int i;
  float minDist=ROWS*COLS;
  Location l;
  int mini=0;
  r=u[m]->getRow();
  c=u[m]->getCol();
  playerName=u[m]->getPlayerName();
  for(i=0;i<NUM;++i){
    if(i!=m&&u[i]&&!u[i]->getDead()&&u[i]->getPlayerName()!=playerName){
      tr=u[i]->getRow();
      tc=u[i]->getCol();
      if(getDist(r,c,tr,tc)<minDist){
        mini=i;
        minDist=getDist(r,c,tr,tc);
      }
    }
  }
  l.r=u[mini]->getRow();
  l.c=u[mini]->getCol();
  l.dirFor=pathDirFor(r,c,l.r,l.c);
  return l;

}

Dir Hastings::manhattenDirFor(Unit *u, int tr, int tc){
  int dr,dc;
  dr = tr-(u->getRow());
  dc = tc-(u->getCol());
  if(abs(dr)>abs(dc)){
    if(dr>=0)return dn;
    else     return up;
  }else{
    if(dc>=0)return rt;
    else     return lt;
  }
}

Dir Hastings::anyDir(Unit *u){
  int r,c;
  int tr,tc;
  r=u->getRow();
  c=u->getCol();
  tr=r-1;tc=c  ;if(tr>=0&&tr<ROWS&&tc>=0&&tc<COLS&&b[tr][tc].what==space)return up;
  tr=r+1;tc=c  ;if(tr>=0&&tr<ROWS&&tc>=0&&tc<COLS&&b[tr][tc].what==space)return dn;
  tr=r  ;tc=c-1;if(tr>=0&&tr<ROWS&&tc>=0&&tc<COLS&&b[tr][tc].what==space)return lt;
  tr=r  ;tc=c+1;if(tr>=0&&tr<ROWS&&tc>=0&&tc<COLS&&b[tr][tc].what==space)return rt;
  return none;
}



SitRep Hastings::makeSitRep(Unit *u[NUM],int m){
  if(!u[m])exit(5);
  SitRep s;
  int i,j;
  for(i=0;i<ROWS;++i)for(j=0;j<COLS;++j)s.board[i][j]=b[i][j];
  s.nearestEnemyCrown = getNearestEnemyCrown(u,m);
  s.nearestEnemy = getNearestEnemy(u,m);
  s.anyOpenSpace = anyDir(u[m]);
  return s;
}

int Hastings::totalHp(Unit *u[], int m){
  int i,sum=0;
  for(i=0;i<NUM;++i)if(u[i]&&u[i]->getPlayerName()==players[m]) sum+=u[i]->getHp();
  return sum;
}

void Hastings::display(Unit* u[])
{
  int i,j;
  int lsize;
  int rsize;
  if(ANSI)lsize = (numplayers*3)+((numplayers-1)*5);
  else lsize = 29;
  rsize=(COLS-lsize)/2;
  if(!TINYMAP){rsize=(COLS*2-lsize)/2;}

  // don't display anything if we are doing the rankings
  if(AUTOTOURNEY)return;

  for (i = 0; i < NUM; ++i)
  {
    if (u[i])
    {
      unit2thing(u[i], u[i]->getRow(), u[i]->getCol());
    }
  }

  // throw a legend out at the top
  color[0]="\033[0;31m";
  color[1]="\033[0;35m";
  color[2]="\033[0;36m";
  color[3]="\033[0;37m";

  for(i = 0; i < rsize; ++i)
  {
    sout << " ";
  }

  if(ANSI)
  {
    for(i = 0; i < numplayers; ++i)
    {
      sout << color[i] << players[i] << " " << totalHp(u,i) << "\033[0m     ";
    }
  }
  else
  {
    sout <<players[0]<<" (lowercase)     "<<players[1]<<" (CAPS)";
  }

  sout << "\n ";
  for(i=0;i<COLS;++i)sout<<"-";
  if(!TINYMAP) for(i=0;i<COLS;++i)sout<<"-";
  sout << "\n";

  // down to business
  for(i=0;i<ROWS;++i){
    sout<<"|";
    for(j=0;j<COLS;++j){
      // if it's open space
      if(b[i][j].what==space){
        if(DOTS) sout<<".";
        else     sout<<" ";
        if(!TINYMAP)sout<<" ";
         continue;
      }

      // if it's a rock
      if(b[i][j].what==rock)
      {
        sout << "X";
        if(!TINYMAP)
        {
          sout << " ";
        }
        continue;
       }

      //else it's a unit
      //turn on some colors if ANSI set
      if(ANSI){
        if(b[i][j].playerName==players[0]) sout << "\033[0;31m";
        if(b[i][j].playerName==players[1]) sout << "\033[0;35m";
        if(b[i][j].playerName==players[2]) sout << "\033[0;36m";
        if(b[i][j].playerName==players[3]) sout << "\033[0;37m";
      }

      //spit out the appropirate unit character
      if(ANSI || b[i][j].playerName==players[0]){
        switch(b[i][j].rank){
        case infantry: sout<<"i";break;
        case archer:   sout<<"a";break;
        case knight:   sout<<"k";break;
        case crown:    sout<<"*";break;
        default:       sout<<"?";break;
        }
      }else{
        switch(b[i][j].rank){
        case infantry: sout<<"I";break;
        case archer:   sout<<"A";break;
        case knight:   sout<<"K";break;
        case crown:    sout<<"*";break;
        default:       sout<<"?";break;
        }
      }

      //indicate direction if there is space
      if(!TINYMAP){
        switch(b[i][j].dir){
        case up:  sout<<"^";break;
        case dn:  sout<<"v";break;
        case rt:  sout<<">";break;
        case lt:  sout<<"<";break;
        default: sout<<"?";break;
        }
      }

      //turn off the colors if we set them earlier
      if(ANSI)sout << "\033[0m";
    }
    sout << "|";
    sout << "\n";
  }

  sout << " ";

  for (i = 0; i < COLS; ++i)
  {
    sout << "-";
  }

  if (!TINYMAP)
  {
    for (i = 0; i < COLS; ++i)
    {
      sout << "-";
    }
  }

  sout << "\n";
  sout << "=~=" << endl;
}


void Hastings::readMap()
{  
  int i,j,rows,cols;
  ifstream  fin;
  fin.open(INFILE);
  fin>>rows;
  fin>>cols;
  fin>>numplayers;

  if(rows!=ROWS || cols!=COLS){
    cout << "error reading map: ROW/COL mismatch with #define in infantry.h.  exiting.\n";
    exit(1);
  }
  if(numplayers>4){
    cout << "error reading map: max 4 players (more requested).  exiting.\n";
    exit(2);
  }
  if(NUM%numplayers!=0){
    cout << "error reading map: total number of units can't be evenly divided.  exiting.\n";
    exit(3);
  }
  for(i=0;i<numplayers;++i){
    fin>>startBox[i].minr;
    fin>>startBox[i].maxr;
    fin>>startBox[i].minc;
    fin>>startBox[i].maxc;
  }

  // max 2 players for non-ANSI terminal
  if(numplayers>2&&!ANSI)numplayers=2;

  for(i=0;i<ROWS;++i){
    for(j=0;j<COLS;++j){
      b[i][j].what=space;
      fin >> c[i][j];
      if(c[i][j]=='X'){
        b[i][j].dir = none;
        b[i][j].what = rock;
      }
    }
  //cout << endl;
  }
  fin.close();
}


void Hastings::printNameList()
{
  for (int i = 0; i < NUM_NAMES; ++i)
  {
    cout << nameList[i] << " ";
    if (i % 11 == 0)
    {
      cout << endl;
    }
  }
  cout << endl;
}


bool Hastings::checksOut(string name){
  int i;
  for(i=0;i<NUM_NAMES;++i){
    if(nameList[i]==name)return true;
  }
  return false;
}

Unit* Hastings::newUnit(string player, Rank rank)
{
  int hp;

  switch(rank)
  {
    case infantry:
      hp = INFANTRYHP;
      break;

    case archer:
      hp = ARCHERHP;
      break;

    case knight:
      hp = KNIGHTHP;
      break;

    case crown:
      hp = CROWNHP;
      break;
  }

  Unit* pNewUnit = NULL;

  #include "makeSoldier.txt"

  pNewUnit->r = 0;
  pNewUnit->c = 0;
  pNewUnit->hp = hp;
  pNewUnit->dir = up;
  pNewUnit->rank = rank;
  pNewUnit->dead = false;
  pNewUnit->playerName = player;

  return pNewUnit;
}

void Hastings::updateB(Unit* u)
{
  if(!u)
  {
    exit(5);
  }

  b[u->getRow()][u->getCol()].what=unit;
  b[u->getRow()][u->getCol()].rank=u->getRank();
  b[u->getRow()][u->getCol()].playerName=u->getPlayerName();
  b[u->getRow()][u->getCol()].dir=u->getDir();
  b[u->getRow()][u->getCol()].hp=u->getHp();
}

bool Hastings::readScenario(UnitCounts counts[], string sFile)
{
  ifstream fin(sFile);

  if (!fin)
  {
    return false;
  }

  fin >> counts[0].crowns;
  fin >> counts[0].knights;
  fin >> counts[0].archers;
  fin >> counts[0].infantry;

  fin >> counts[1].crowns;
  fin >> counts[1].knights;
  fin >> counts[1].archers;
  fin >> counts[1].infantry;

  fin.close();
  return true;
}

bool Hastings::setUpBoard(Unit* u[NUM], string sFile)
{
  UnitCounts scenario[2];
  readMap();
  if (!readScenario(scenario, sFile))
  {
    cout << "Invalid scenario file specified" << endl;
    return false;
  }

  int unitCounter = 0;

  for(int i = 0; i < NUM; ++i)
  {
    u[i] = 0;
  }

  for(int i = 0; i < numplayers; ++i)
  {
tryagain:
    cout << "Player " << i << ": ";
    cin >> players[i];

    if(players[i] == "?")
    {
      printNameList();
      goto tryagain;
    }

    if(!checksOut(players[i]))
    {
      cout << "That player is not in the list.\n";
      cout << "type '?' to see a full list.\n";
      goto tryagain;
    }
  }

  cout << "=~=" << endl;

  for (int pnum = 0; pnum < numplayers; ++pnum)
  {
    // make all the crowns
    for(int i = 0; i < scenario[pnum].crowns; ++i)
    {
      u[unitCounter] = newUnit(players[pnum],crown);
      Location loc = u[unitCounter]->Place(startBox[pnum],makeSitRep(u,unitCounter));
      validatePlacement(u, startBox[pnum], loc, unitCounter);      
      updateB(u[unitCounter]);
      ++unitCounter;
    }

    // make all the knights
    for(int i = 0; i < scenario[pnum].knights; ++i)
    {
      u[unitCounter] = newUnit(players[pnum],knight);
      Location loc = u[unitCounter]->Place(startBox[pnum],makeSitRep(u,unitCounter));
      validatePlacement(u, startBox[pnum], loc, unitCounter);
      updateB(u[unitCounter]);
      ++unitCounter;
    }

    // make all the archers
    for(int i = 0; i < scenario[pnum].archers; ++i)
    {
      u[unitCounter] = newUnit(players[pnum],archer);
      Location loc = u[unitCounter]->Place(startBox[pnum],makeSitRep(u,unitCounter));
      validatePlacement(u, startBox[pnum], loc, unitCounter);
      updateB(u[unitCounter]);
      ++unitCounter;
    }

    // make all the infantry
    for(int i = 0; i < scenario[pnum].infantry; ++i)
    {
      u[unitCounter] = newUnit(players[pnum], infantry);
      Location loc = u[unitCounter]->Place(startBox[pnum], makeSitRep(u,unitCounter));
      validatePlacement(u, startBox[pnum], loc, unitCounter);
      updateB(u[unitCounter]);
      ++unitCounter;
    }
  }

  return true;
}

void Hastings::validatePlacement(Unit* u[NUM], Box startBox, Location loc, int unitCounter)
{
  if ((b[loc.r][loc.c].what == space) && (loc.r >= startBox.minr) && (loc.r <= startBox.maxr) && (loc.c >= startBox.minc) && (loc.c <= startBox.maxc))
  {
    u[unitCounter]->r = loc.r;
    u[unitCounter]->c = loc.c;
    u[unitCounter]->dir = loc.dirFor;
  }
  else if (u[unitCounter]->rank == crown)
  {
    // Put the crown in the bounding box so the game can continue
    u[unitCounter]->r = startBox.minr;
    u[unitCounter]->c = startBox.minc;
    u[unitCounter]->dir = up;
  }
  else
  {
    // Invalid placement - kill unit
    u[unitCounter]->dead = true;
  }
}

//return the number of spaces the unit can move without hitting someting,
//up to dist
int Hastings::clear(Unit *u[], int m, int dist){
  if(!u[m])exit(5);
  int i;
  int goDist=0;
  //initialize x and y to the unit's location
  int tr=u[m]->getRow();
  int tc=u[m]->getCol();

  for(i=0;i<dist;++i){
    //move tr and tc to be in front of the unit's location
    switch(u[m]->getDir()){
    case up:tr--;break;
    case dn:tr++;break;
    case lt:tc--;break;
    case rt:tc++;break;
    case none:break;
    }

    // is that space off the board?
    if(tr<0||tr>=ROWS||tc<0||tc>=COLS)break;

    // is there a something there?
    if(b[tr][tc].what!=space)break;

    //nothing there?  bump the goDist
    ++goDist;
  }

  return goDist;
}

void Hastings::arrowSuffer(Unit *u[],int m,int ar,int ac,int hits){
  int sr,sc,er,ec;

  if(!u[m])exit(5);
  int i;
  //initialize x and y to the unit's location
  int tr=u[m]->getRow();
  int tc=u[m]->getCol();

  //find the box the archer can target
  switch(u[m]->getDir()){
  case up: sr=tr-3;er=tr-1;sc=tc-1;ec=tc+1;break;
  case dn: sr=tr+1;er=tr+3;sc=tc-1;ec=tc+1;break;
  case lt: sr=tr-1;er=tr+1;sc=tc-3;ec=tc-1;break;
  case rt: sr=tr-1;er=tr+1;sc=tc+1;ec=tc+3;break;
  case none: return;
  }

  if(sr<0)sr=0;if(er>=ROWS)er=ROWS-1;
  if(sc<0)sc=0;if(ec>=COLS)ec=COLS-1;

  //return if the target is not in range
  if(ar<sr||ar>er||ac<sc||ac>ec)return;



  //check to see if any living unit occupies space [ar,ac]
  for(i=0;i<NUM;++i){
    if(u[i]&&!u[i]->getDead()&&u[i]->getRow()==ar&&u[i]->getCol()==ac){
      //if so, make it suffer
      u[i]->Suffer(hits);
      if(u[i]->getDead()){
        delete u[i];
        u[i]=0;
      }
    }
  }

  //nobody there? then just return
  return;
}



//make an attacked unit suffer hits
void Hastings::makeSuffer(Unit *u[], int m, int hits){
  if(!u[m])exit(5);
  int i;
  //initialize x and y to the unit's location
  int tr=u[m]->getRow();
  int tc=u[m]->getCol();

  //move tr and tc to be in front of the unit's location
  switch(u[m]->getDir()){
  case up:tr--;break;
  case dn:tr++;break;
  case lt:tc--;break;
  case rt:tc++;break;
  case none:break;
  }

  //check to see if any living unit occupies space [x,y]
  for(i=0;i<NUM;++i){
    if(u[i]&&!u[i]->getDead()&&u[i]->getRow()==tr&&u[i]->getCol()==tc){
      //if so, make it suffer
      u[i]->Suffer(hits);
      if(u[i]->getDead()){
        delete u[i];
        u[i]=0;
      }
    }
  }

  //nobody there? then return false
  return;
}

void Hastings::autoTourney(Unit *u[NUM])
{
  //TODO: write this
  return;
}

bool Hastings::oneLeft(Unit *u[NUM])
{
  int i;
  string firstTla;
  string secondTla;

  //get the first crown tla
  for(i=0;i<NUM;++i){
    if(u[i]&&u[i]->getRank()==crown){
      firstTla=u[i]->getPlayerName();
      break;
    }
  }
  if(i==NUM){
    //both kings are dead
    cout << "Both crowns die! Everyone wins. \n";
    return true;
  }
  //get the second crown tla
  for(i=0;i<NUM;++i){
    if(u[i]&&u[i]->getRank()==crown&&u[i]->getPlayerName()!=firstTla){
      secondTla=u[i]->getPlayerName();
      break;
    }
  }

  if(i == NUM)
  {
    //only one king lives
    cout << "The one true crown! " << firstTla << " wins. \n";
    return true;
  }

  //get the first tla
  for(i=0;i<NUM;++i){
    if(u[i]){
      firstTla=u[i]->getPlayerName();
      break;
    }
  }

  //look for a different tla
  for(i=0;i<NUM;++i)
  {
    if(u[i]&&u[i]->getPlayerName()!=firstTla){
      return false;
    }
  }

  cout << firstTla << " wins!\n";
  //there can be only one
  return true;
}


void Hastings::doTurn(Unit *u[NUM]){
  int m;
  SitRep sitRep;
  Action a;
  int hits;
  int lr,lc;
  int i,j,t,next[NUM];

  //come up with a random ordering of pieces for this turn
  for(i=0;i<NUM;++i)next[i]=i;
  for(i=NUM-1;i>0;--i){
    j=rand()%i;
    t=next[j];
    next[j]=next[i];
    next[i]=t;
  }

  for(i=0;i<NUM;++i){
    m=next[i];
    if(oneLeft(u))return;;
          if(u[m]&&!u[m]->getDead()){
      makeB(u);
                sitRep=makeSitRep(u,m);
                int tseed=rand();  //Save the current state of rand...
                a=u[m]->Recommendation(sitRep);
                srand(tseed);  //...and reset it.
                switch(a.action){
        case turn:
          u[m]->Turn(a.dir);
          break;
        case fwd:
          lr=u[m]->getRow();
          lc=u[m]->getCol();
          if(!clear(u,m,a.maxDist))break;
          if(u[m]->getRank()==archer||u[m]->getRank()==infantry)
            a.maxDist=1;
          u[m]->Move(clear(u,m,a.maxDist));
          break;
        case attack:
          hits=u[m]->Attack();
          if(u[m]->getRank()==archer)
            arrowSuffer(u,m,a.archerRow,a.archerCol,hits);
          else
            makeSuffer(u,m,hits);
          break;
        case nothing: break;
                }
          }
  }
  return;
}

/*

//run an automatic game.  tla1 and tla2 should be set up prior to calling
int autoGame(gamePiece *p[]){
  bool done=false;
  int x;
  int turns=0;
  setUpBoardx(p);
  while(!done){
    doTurn(p);
    turns++;
    if(oneLeft(p))done=true;
    if(turns>=MAXTURNS)done=true;
  }
  if(turns>=MAXTURNS)return 0;
  for(int i=0;i<NUM;++i){
    if(p[i]->onBoard()&&p[i]->getProvince()==gascogne)return 1;
  }
  return 0;
}

//run a whole tournament of each tla against AUTONUMMATCHES random others, output stats on each
void autoTourney(gamePiece *p[]){
  int i,j,k;
  int wins;
  int w;
  for(i=0;i<NUM_NAMES;++i){
    wins=0;
    strcpy(tla1,nameList[i]);
    for(j=0;j<AUTONUMMATCHES;++j){
      k=rand()%NUM_NAMES;
      while(k==i)k=rand()%NUM_NAMES;
      strcpy(tla2,nameList[k]);
      w=autoGame(p);
      //cout << "\t"<<tla1<<" vs. "<<tla2<<": ";
      //if(w)cout<<"win\n";else cout<<"lose\n";
      wins+=w;
    }
    cout << tla1 << " ";
    cout << wins;
    cout << endl;
  }
  return;
}



******************
*/



