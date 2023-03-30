#include "bats.h"
#include "event.h"
#include "gold.h"
#include "map.h"
#include "pit.h"
#include "room.h"
#include "wumpus.h"

using namespace std;
/***********************************************************************************
 ** Function: default
 ** Description: empty member vars
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
Wumpus::Wumpus(){
   //constructs information for string percept
   percept = "You smell a terrible stench.";
   gridEvent = "Encountered the Wumpus. You are promptly cooked and eaten.";
}
/***********************************************************************************
 ** Function: getPercept
 ** Description: getsPercept
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
string Wumpus::getPercept(){
   return percept;
}
/***********************************************************************************
 ** Function: getEncounter
 ** Description: gets grid event
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
string Wumpus::getEncounter(){
   return gridEvent;
}

Wumpus::~Wumpus(){

}