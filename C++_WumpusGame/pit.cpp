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
Pit::Pit(){
   //constructs the string
   percept = "You feel a breeze.";
   gridEvent = "Encountered a Pit. Who put this here?";
}
/***********************************************************************************
 ** Function: getPercept
 ** Description: getsPercept
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
string Pit::getPercept(){
   return percept;
}
/***********************************************************************************
 ** Function: getEncounter
 ** Description: gets grid event
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
string Pit::getEncounter(){
   return gridEvent;
}

Pit::~Pit(){

}