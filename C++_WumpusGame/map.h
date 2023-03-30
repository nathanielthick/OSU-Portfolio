#ifndef MAP_H
#define MAP_H

#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "bats.h"
#include "event.h"
#include "gold.h"
#include <iostream>
#include <string>
#include <vector>
#include "pit.h"
#include "room.h"
#include "wumpus.h"

using namespace std;

class Map{
    private:
        int size;
        int arrows;
        bool wumpusFlag;
        int adventurerXpos,adventurerYpos,wumpusXpos,wumpusYpos;
        bool goldFlag;
        vector<vector<Room*> > game;
    public:
    void gameEnd();
    double numIn();
    int getIntsOnly();
    int getIntInRange(int low, int high);
    int gameRun();
    int gameRunCheats();
    Map(int);
    void printRoomEvents();
    void giveEvents(int);
    void giveEntrance(int);
    int getMovement();
    void printBoard();
    void setEventsRandLoc(int);
    void batMove();
    bool eventEncounter();
    void printBar();
    int randCoord();
    void setWumpCoord(int x, int y);
    void setAdvCoord(int x, int y);
    void eventRooms();
    void moveUp();
    void moveDown();
    void printCheatBoard();
    void setupMap();
    void moveAdvPos(int);
    void shootArrow(int);
    void wumpusMove();
    void moveLeft();
       void moveRight();
       bool wumpusStatus();
       bool checkArrows();
       void arrowMiss();
       void killWumpus();
       bool getWumpus();
       bool ropeReadventurerYpos();
       ~Map();
      
};

#endif