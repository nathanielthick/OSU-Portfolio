/**********************************************************************************
** Program: Hunt the Wumpus
** Author: Nathaniel Thickett
** Date: 5/23/2021
** Description: Hunt the Wumpus game
** Input: Command line args, first is boards size, enter a second arg to enable cheats
** Output: plays hunt the wumpus
***********************************************************************************/
#include "bats.h"
#include "event.h"
#include "gold.h"
#include "map.h"
#include "pit.h"
#include "room.h"
#include "wumpus.h"
#include <ctime>
using namespace std;
int main(int argc, char** argv){
    bool gamestate = true;
    int modeChoice = 1;
    int size = 5;
    if(argc == 2){
        size = atoi(argv[1]);
    }
    else if(argc == 3){
        size = atoi(argv[1]);
        modeChoice = 2;
    }
    srand(time(0));
    if(size <= 4)
        size = 5;
    else if(size >= 11)
        size = 10;
    Map map = Map(size);
    map.setupMap();//setup map
    if(modeChoice == 1){
        while(modeChoice != 3){
            gamestate = map.eventEncounter();//runs game
            if(gamestate == false){
                map.gameEnd();
                break;
            }
            modeChoice = map.gameRun();
        }
    }
    else if(modeChoice == 2){
        while(modeChoice != 3){
            gamestate = map.eventEncounter();//runs game with cheats
            if(gamestate == false){
                map.gameEnd();
                break;
            }
            modeChoice = map.gameRunCheats();
        }
    }
    if(modeChoice == 3){
        map.gameEnd();
    }
    return 0;
}