#include "bats.h"
#include "event.h"
#include "gold.h"
#include "pit.h"
#include "room.h"
#include "wumpus.h"
#include "map.h"


using namespace std;
/***********************************************************************************
 ** Function: default
 ** Description: empty member vars
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
Bats::Bats(){
   percept = "You hear wings flapping.";
   gridEvent = "Encountered Bats. They somehow make you teleport to another random location.";
}
/***********************************************************************************
 ** Function: getPercept
 ** Description: getsPercept
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
string Bats::getPercept(){
   return percept;
}
/***********************************************************************************
 ** Function: getEncounter
 ** Description: gets grid event
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
string Bats::getEncounter(){
   return gridEvent;
}

Bats::~Bats(){

}