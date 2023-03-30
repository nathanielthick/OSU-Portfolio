#include "bats.h"
#include "pit.h"
#include "room.h"
#include "event.h"
#include "map.h"
#include "wumpus.h"
#include "gold.h"


using namespace std;

/***********************************************************************************
 ** Function: default constructor
 ** Description: 
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
Room::Room(){
   supposedEvent = 0;
   adventurer = false;
}
/***********************************************************************************
 ** Function: getAdvPStatus
 ** Description:returns room adv status
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
bool Room::getAdvPStatus(){
   return adventurer;
}
/***********************************************************************************
 ** Function: setAdvSquareStatus
 ** Description: sets adv status
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
void Room::setAdvSquareStatus(bool newAdventurer){
   adventurer = newAdventurer;
}

/***********************************************************************************
 ** Function: getSupposedEvent
 ** Description: gets event
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
int Room::getSupposedEvent(){
   return supposedEvent;
}
/***********************************************************************************
 ** Function: setSupposedEvent
 ** Description: sets event
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
void Room::setSupposedEvent(int newsupposedEvent){
   supposedEvent = newsupposedEvent;
}
/***********************************************************************************
 ** Function: getEvent
 ** Description: gets event
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
string Room::getEvent(){
   return events.getPercept();
   cout << "event got" << endl;
}

/***********************************************************************************
 ** Function: getEntrance
 ** Description: gets emntrance events
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
string Room::getEntrance(){
   return events.getEncounter();
}

/***********************************************************************************
 ** Function: setRoomEventActual
 ** Description: sets actual room event object
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
void Room::setRoomEventActual(int newEvent){
   Wumpus wumpus;
   Pit pit;
   Bats bats;
   Gold gold;
   Event event;
   switch(newEvent){
       case 2:
           events = wumpus;
           break;
       case 3:
           events = gold;
           break;
       case 4:
           events = pit;
           break;
       case 5:
           events = bats;
           break;
       default:
           events = event;
           break;
   }
}


Room::~Room(){
}