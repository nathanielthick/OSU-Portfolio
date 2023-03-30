#include "bats.h"
#include "event.h"
#include "map.h"
#include "pit.h"
#include "room.h"
#include "gold.h"


using namespace std;

/***********************************************************************************
 ** Function: default
 ** Description: empty member vars
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
Event::Event(){
   //percept here is unutilized, held in place for ease of implementation
   percept = "";
   gridEvent = "";
}


/***********************************************************************************
 ** Function: getEncounter
 ** Description: getsEncounter
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
string Event::getEncounter(){
   return gridEvent;
}
/***********************************************************************************
 ** Function: operator overload for =
 ** Description: 
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
Event& Event::operator=(const Event &event){
    percept = event.percept;
    gridEvent = event.gridEvent;
 
    // return the existing object so we can chain this operator
    return *this;
}

/***********************************************************************************
 ** Function: getPercept
 ** Description: egets percept
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
string Event::getPercept(){
   //returns the blank strring used for a percept
   return percept;
}


Event::~Event(){

}