#ifndef ROOM_H
#define ROOM_H

#include <cstdlib>
#include <ctime>
#include "bats.h"
#include "event.h"
#include "gold.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "pit.h"
#include "wumpus.h"

using namespace std;

class Room {
   private:
       Event events;
       int supposedEvent;
       bool adventurer;  
   public:
       Room();
       int getSupposedEvent();
       void setSupposedEvent(int);
       bool getAdvPStatus();
       void setAdvSquareStatus(bool);
       void setRoomEventActual(int);
       string getEntrance();
       string getEvent();
       ~Room();
};

#endif