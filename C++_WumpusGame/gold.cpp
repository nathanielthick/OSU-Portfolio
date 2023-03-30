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
Gold::Gold(){
   percept = "You see a glimmer nearby.";
   gridEvent = "Encountered the Gold. huh, shiny.";
}
/***********************************************************************************
 ** Function: getPercept
 ** Description: getsPercept
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
string Gold::getPercept(){
   return percept;
}
/***********************************************************************************
 ** Function: getEncounter
 ** Description: gets grid event
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
string Gold::getEncounter(){
   return gridEvent;
}

Gold::~Gold(){

}