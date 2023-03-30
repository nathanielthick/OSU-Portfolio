#include "bats.h"
#include "event.h"
#include "gold.h"
#include "map.h"
#include "pit.h"
#include "room.h"
#include "wumpus.h"
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

using namespace std;

/***********************************************************************************
 ** Function: default constructor
 ** Description: takes size from cmd arg and makes map
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
Map::Map(int setSize){
   size = setSize;
   for(int i = 0; i < size; i++){
       vector<Room*> inner;
       for (int j = 0; j < size; j++){
           inner.push_back(new Room);//sets up 2d vector
       }
       game.push_back(inner);
   }
   arrows = 3;
   wumpusFlag = false;
   goldFlag = false;
}

/***********************************************************************************
 ** Function: getMovement
 ** Description: for wasd movement, doesnt work :(
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
int Map::getMovement(){
        cin.clear(); // clears cin
        cin.ignore(80, '\n'); // claer memory of inputs
        struct termios old_tio, new_tio;
        unsigned char ch;
        tcgetattr(STDIN_FILENO,&old_tio);
        new_tio=old_tio;
        new_tio.c_lflag &=(~ICANON & ~ECHO);
        tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);
        ch = getchar(); 
        tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
        switch(ch){
            case 'W':
                return 1;
                break;
            case 'w':
                return 1;
                break;
            case 'A':
                return 3;
                break;
            case 'a':
                return 3;
                break;
            case 's':
                return 2;
                break;
            case 'S':
                return 2;
                break;
            case 'D':
                return 4;
                break;
            case 'd':
                return 4;
                break;
            default:
                return 5;

        }
        

}


/***********************************************************************************
 ** Function: printCheatBoard
 ** Description: prints board with cheats enabled
 ** Parameters: NA
 ** Pre-condtitions: board
 ** Post-conditions: board is printed with cheats
 ***********************************************************************************/
void Map::printCheatBoard(){
    printBar();
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            switch(game[i][j]->getAdvPStatus()){
                case 0:
                    switch(game[i][j]->getSupposedEvent()){
                        case 0:
                            cout << " ";
                            break;
                        case 2://prints grid with cheat marks
                            cout << "W";
                            break;
                        case 3:
                            cout << "G";
                            break;
                        case 4:
                            cout << "P";
                            break;
                        case 5:
                            cout << "B";
                            break;
                    }
                    break;
                case 1:
                    cout << "*";
                    break;
            }
            cout << " | ";
        }
    cout << "\n";
    printBar();
    }
}

/***********************************************************************************
 ** Function: printBar
 ** Description: prints bar for top and bottom of map
 ** Parameters: NA
 ** Pre-condtitions: board
 ** Post-conditions: bar is printed
 ***********************************************************************************/
void Map::printBar(){
    for(int i = 0; i < size; i++)//prints bar
        cout << "____";
    cout << "\n";
}

/***********************************************************************************
 ** Function: printBoard
 ** Description: prints board
 ** Parameters: NA
 ** Pre-condtitions: board
 ** Post-conditions: board is printed
 ***********************************************************************************/
void Map::printBoard(){
   printBar();
   for(int i = 0; i < size; i++){
       for(int j = 0; j < size; j++){
           switch(game[i][j]->getAdvPStatus()){//prints * for player character
               case 0:
                   cout << " ";
                   break;
               case 1:
                   cout << "*";
                   break;
           }
           cout << " | ";
       }
   cout << "\n";
   printBar();
   }
}

/***********************************************************************************
 ** Function: randCoord
 ** Description: returns random coord within size
 ** Parameters: NA
 ** Pre-condtitions: board
 ** Post-conditions: NA
 ***********************************************************************************/
int Map::randCoord(){
    int x;
    x = rand()%size;//makes random coordinate inbounbds
    return x;
}

/***********************************************************************************
 ** Function: setWumpCoord
 ** Description: sets new wumpus coords
 ** Parameters: NA
 ** Pre-condtitions: board
 ** Post-conditions: NA
 ***********************************************************************************/
void Map::setWumpCoord(int x, int y){
    wumpusXpos = x;//sets new wump coords
    wumpusYpos = y;
}



/***********************************************************************************
 ** Function: setEventsRandLoc
 ** Description: sets events at random locations
 ** Parameters: int for type of event
 ** Pre-condtitions: board
 ** Post-conditions: events
 ***********************************************************************************/
void Map::setEventsRandLoc(int type){
    int tempXval,tempYval;
    bool flag = false;
    while (flag == false){
        tempXval = randCoord();
        tempYval = randCoord();
        if(game[tempXval][tempYval]->getSupposedEvent() == 0){
            game[tempXval][tempYval]->setSupposedEvent(type);//if event is empty is grid location, sets event
            flag = true;
            if(type == 1){
                setAdvCoord(tempXval, tempYval);
                game[adventurerXpos][adventurerYpos]->setAdvSquareStatus(true);
            }
            if(type == 2){
                setWumpCoord(tempXval, tempYval);
            }
        }
        
    }

}

/***********************************************************************************
 ** Function: eventRooms
 ** Description: sets room events to what they should be
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
void Map::eventRooms(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(game[i][j]->getSupposedEvent() != 1)
                game[i][j]->setRoomEventActual(game[i][j]->getSupposedEvent());//sets actual room events
        }
    }
}

/***********************************************************************************
 ** Function: setupMap
 ** Description: sets up map with random events in rooms
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
void Map::setupMap(){
   setEventsRandLoc(1);
   setEventsRandLoc(2);
   setEventsRandLoc(3);//sets randome events in map
   setEventsRandLoc(4);
   setEventsRandLoc(4);
   setEventsRandLoc(5);
   setEventsRandLoc(5);
   eventRooms();
}

/***********************************************************************************
 ** Function: moveUp
 ** Description: moved player up
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
void Map::moveUp(){
    game[adventurerXpos][adventurerYpos]->setAdvSquareStatus(false);
    adventurerXpos--;
    game[adventurerXpos][adventurerYpos]->setAdvSquareStatus(true);
}

/***********************************************************************************
 ** Function: moveDown
 ** Description: moved player down
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
void Map::moveDown(){
    game[adventurerXpos][adventurerYpos]->setAdvSquareStatus(false);
    adventurerXpos++;
    game[adventurerXpos][adventurerYpos]->setAdvSquareStatus(true);
}

/***********************************************************************************
 ** Function: moveLeft
 ** Description: moved player left
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
void Map::moveLeft(){
    game[adventurerXpos][adventurerYpos]->setAdvSquareStatus(false);
    adventurerYpos--;
    game[adventurerXpos][adventurerYpos]->setAdvSquareStatus(true);
}

/***********************************************************************************
 ** Function: moveright
 ** Description: moved player right
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
void Map::moveRight(){
    game[adventurerXpos][adventurerYpos]->setAdvSquareStatus(false);
    adventurerYpos++;
    game[adventurerXpos][adventurerYpos]->setAdvSquareStatus(true);
}


/***********************************************************************************
 ** Function: moveAdvPos
 ** Description: moves adventure in int direction
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
void Map::moveAdvPos(int tempDirection){
    if(tempDirection==1 && (adventurerXpos-1)>=0){
        moveUp();
    }
    if(tempDirection==2 && (adventurerXpos+1) < size){
        moveDown();
    }
    if(tempDirection==3 && (adventurerYpos-1) >= 0){
        moveLeft();   
    }
    if(tempDirection==4 && (adventurerYpos+1) < size){//moves adventurer in direction if valid
        moveRight();  
    }
    else{
        cout << "Move is Out of Map\n";
    }
}

/***********************************************************************************
 ** Function: wumpus status
 ** Description: returns whetehr or not wumpus is dead
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: arrows
 ***********************************************************************************/
bool Map::wumpusStatus(){
    if(wumpusFlag == true){
        cout << "The wumpus is dead \n";//returns wumpus condition
        return true;
    }
    return false;
}

/***********************************************************************************
 ** Function: shootArrow
 ** Description: sets up map with random events in rooms
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
void Map::shootArrow(int tempDirection){
    int temXposit = adventurerXpos;
    int temYposit = adventurerYpos;
    bool wumpusDED = wumpusStatus();
    if(wumpusDED){
        return;
    }
    for(int i = 0; i < 3; i++){
        if(tempDirection==1){
            if((temXposit-1)>=0){
                temXposit = temXposit - 1;//shoots arrow and scans for wumpus
            }
        }
        else if(tempDirection == 2){
            if((temXposit+1) < size){
                temXposit = temXposit + 1;
            }
        }
        else if(tempDirection==3){
            if((temYposit-1) >= 0){
                temYposit = temYposit - 1;
            }
        }
        else if(tempDirection==4){
            if((temYposit+1) < size){
                temYposit = temYposit + 1;
            }
        }
        if(temXposit == wumpusXpos){
            if(temYposit == wumpusYpos){
                killWumpus();
                break;
            }
       }
    }
    if(wumpusFlag == false){
        wumpusMove();
    }
}

/***********************************************************************************
 ** Function: killWumpus
 ** Description: kills the wumpus 
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
void Map::killWumpus(){
    cout << "The wumpus was piered by the arrow\n";
    cout << "The wumpus is now dead\n";
    game[wumpusXpos][wumpusYpos]->setSupposedEvent(0);
    game[wumpusXpos][wumpusYpos]->setRoomEventActual(0);//wumpus is removed
    wumpusFlag = true;
}

/***********************************************************************************
 ** Function: giveEvents
 ** Description: gives events
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
void Map::giveEvents(int eventNum){
    if(eventNum == 2){
        cout << "You smell a terrible stench." << endl;
    }
    else if(eventNum == 3){
        cout << "You see a glimmer nearby." << endl;
    }
    else if(eventNum == 4){
        cout << "You feel a breeze." << endl;
    }
    else if(eventNum == 5){
        cout << "You hear wings flapping." << endl;
    }
}

/***********************************************************************************
 ** Function: giveEntrance
 ** Description: sgives entrence event to room
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
void Map::giveEntrance(int eventNum){
    if(eventNum == 2){
        cout << "Encountered the Wumpus. You are promptly cooked and eaten." << endl;
    }
    else if(eventNum == 3){
        cout << "Encountered the Gold. huh, shiny." << endl;
    }
    else if(eventNum == 4){
        cout << "Encountered a Pit. Who put this here?" << endl;
    }
    else if(eventNum == 5){
        cout << "Encountered Bats. They somehow make you teleport to another random location." << endl;
        cout << "dont ask how." << endl;
    }
}

/***********************************************************************************
 ** Function: printRoomEvents
 ** Description: prints room events
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
void Map::printRoomEvents(){
    cout << "Events Near You:\n";
    if((adventurerXpos + 1) < size){
        if(game[adventurerXpos+1][adventurerYpos]->getSupposedEvent() != 1){
            giveEvents(game[adventurerXpos+1][adventurerYpos]->getSupposedEvent());
        }
   }
    if((adventurerXpos - 1) >= 0){
        if(game[adventurerXpos-1][adventurerYpos]->getSupposedEvent() != 1){
            giveEvents(game[adventurerXpos-1][adventurerYpos]->getSupposedEvent());
        }
    }
    if((adventurerYpos + 1) < size){
        if(game[adventurerXpos][adventurerYpos+1]->getSupposedEvent() != 1){
            giveEvents(game[adventurerXpos][adventurerYpos+1]->getSupposedEvent());
        }
    }
    if((adventurerYpos - 1) >= 0){
        if(game[adventurerXpos][adventurerYpos-1]->getSupposedEvent() != 1){
            giveEvents(game[adventurerXpos][adventurerYpos-1]->getSupposedEvent());
        }
    }
}

/***********************************************************************************
 ** Function: gameRun
 ** Description: runs game in non-cheat mode
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
int Map::gameRun(){
    int selection, direction;
    printBoard();
    printRoomEvents();
    cout << "Enter value to choose action:" << endl;
    cout << "1) MOVE" << endl;
    cout << "2) SHOOT" << endl;
    cout << "3) QUIT" << endl;
    selection = getIntInRange(1,3);
    if(selection == 1){
        cout << "Enter value to choose direction:" << endl;
        cout << "1) UP" << endl;
        cout << "2) DOWN" << endl;
        cout << "3) LEFT" << endl;
        cout << "4) RIGHT" << endl;
        direction = getIntInRange(1,4);
        moveAdvPos(direction);
    }
    else if(selection == 2){
        cout << "Enter value to choose direction:" << endl;
        cout << "1) UP" << endl;
        cout << "2) DOWN" << endl;
        cout << "3) LEFT" << endl;
        cout << "4) RIGHT" << endl;
        direction = getIntInRange(1,4);
        shootArrow(direction);
    }
    else{
        return 3;
    }
    return 1;
}

/***********************************************************************************
 ** Function: gameRun
 ** Description: runs game in cheat mode
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
int Map::gameRunCheats(){
    int selection, direction;
    printCheatBoard();
    printRoomEvents();
    cout << "Enter value to choose action:" << endl;
    cout << "1) MOVE" << endl;
    cout << "2) SHOOT" << endl;
    cout << "3) QUIT" << endl;
    selection = getIntInRange(1,3);
    if(selection == 1){
        cout << "Enter value to choose direction:" << endl;
        cout << "1) UP" << endl;
        cout << "2) DOWN" << endl;
        cout << "3) LEFT" << endl;
        cout << "4) RIGHT" << endl;
        direction = getIntInRange(1,4);
        moveAdvPos(direction);
    }
    else if(selection == 2){
        cout << "Enter value to choose direction:" << endl;
        cout << "1) UP" << endl;
        cout << "2) DOWN" << endl;
        cout << "3) LEFT" << endl;
        cout << "4) RIGHT" << endl;
        direction = getIntInRange(1,4);
        shootArrow(direction);
    }
    else{
        return 3;
    }
    return 2;
}

/***********************************************************************************
 ** Function: gameEnd
 ** Description: deletes rooms
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
void Map::gameEnd(){
    for(int i = 0; i < size; i++){
       for (int j = 0; j < size; j++){
           delete game[i][j];
       }
   }
}

/***********************************************************************************
 ** Function: numIn
 ** Description: takes input and guarentees it is a float or int
 ** Parameters: NA
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
double Map::numIn() {
  double num; 
  while (!(cin >> num)) { // runs while cin doesnt work, ie wrong type input
    cin.clear(); // clears cin
    cin.ignore(80, '\n'); // claer memory of inputs
    cout << "Please enter a number.  Try Again: ";
  }
  cin.ignore(80, '\n');  // clear memory of inputs
  return num;
}
/***********************************************************************************
 ** Function: getIntsOnly
 ** Description: loops numIn until valid integer input is received
 ** Parameters: NA
 ** Pre-condtitions: numIn
 ** Post-conditions: NA
 ************************************************************************************/
int Map::getIntsOnly() {
  double num = numIn(); // numIn ensures a numerical input
  while (num != static_cast<int>(num)) { // checks if num is type int by comparing it to itself with cast to int
    cout << "Integers only please.  Try Again: ";
    num = numIn();
  }
  return static_cast<int>(num);
}
/***********************************************************************************
 ** Function: GetIntInRange
 ** Description: used getIntsOnly and numIn to get an integer withing specifed range
 ** Parameters: low int and high int to be used as range
 ** Pre-condtitions: NA
 ** Post-conditions: NA
 ***********************************************************************************/
int Map::getIntInRange(int low, int high) {
  int num = getIntsOnly();  // Ensures a number and an integer
  while (num < low || num > high) {
    cout << "Integer must be from " << low << " to " << high << ".  Try Again: ";
    num = getIntsOnly();
  }
  return num;
}

/***********************************************************************************
 ** Function: arrowMiss
 ** Description: when arrow misses
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
void Map::arrowMiss(){
    cout << "you missed your arrow\n" << endl;
    arrows--;
    cout << arrows << " Arrows Remain\n" << endl;
}

/***********************************************************************************
 ** Function: wumpusMove
 ** Description: moves wumpus after arrow miss
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
void Map::wumpusMove(){
    arrowMiss();
    int chance = rand()%20;
    if(chance <= 5){
        cout << "The wumpus will now move.\n";
        game[wumpusXpos][wumpusYpos]->setSupposedEvent(0);
        game[wumpusXpos][wumpusYpos]->setRoomEventActual(0);
        setEventsRandLoc(2);
        game[wumpusXpos][wumpusYpos]->setRoomEventActual(2);
    }
}

/***********************************************************************************
 ** Function: setAdvCoord
 ** Description: sets adventurer coordinates
 ** Parameters: NA
 ** Pre-condtitions: board
 ** Post-conditions: NA
 ***********************************************************************************/
void Map::setAdvCoord(int x, int y){
    adventurerXpos = x;
    adventurerYpos = y;
}

/***********************************************************************************
 ** Function: batMove
 ** Description: teleports player to new loc
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
void Map::batMove(){
    int tempXval,tempYval;
    bool checker = true;
    game[adventurerXpos][adventurerYpos]->setAdvSquareStatus(false);
    while(checker == true){
        tempXval = randCoord();
        tempYval = randCoord();
        if(game[tempXval][tempYval]->getSupposedEvent() == 0){//only valid non event squares
            setAdvCoord(tempXval, tempYval);
            game[adventurerXpos][adventurerYpos]->setAdvSquareStatus(true);
            checker = false;
        }
    }
}

/***********************************************************************************
 ** Function: checkArrows
 ** Description: checks if arrows are out
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
bool Map::checkArrows(){
    if(arrows == 0){
        if(wumpusFlag == false){
            cout << "You have zero arrows remaining." << "\n\n";
            cout << "The wumpus is not dead. You lose." << "\n\n";
            return false;//ends game if out of arrows
        }
        else{
            cout << "You have zero arrows remaining." << "\n\n";
            cout << "The wumpus is dead. You may continue." << "\n\n";
        }
       
    }
    return true;
}

/***********************************************************************************
 ** Function: ropeReadadventurerYpos
 ** Description: checks rope for winning
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
bool Map::ropeReadventurerYpos(){
    if(goldFlag == true){
        if(wumpusFlag == true){
            cout << "You have the gold and you killed the wumpus" << endl;
            cout << "Congratulations you win" << "\n\n";
            return false;
        }
    }
    if(goldFlag == true){
        if(wumpusFlag == false){
            cout << "You have the gold but you havent killed the wumpus" << endl;
            cout << "You must continue" << "\n\n";
            return true;
        }
    }
    if(goldFlag == false){
        if(wumpusFlag == false){
            cout << "You have neither the gold nor the head of the wumpus" << endl;
            cout << "You must continue" << "\n\n";
            return true;
        }
    }
    if(goldFlag == false){
        if(wumpusFlag == true){
            cout << "You have the head of the beast, but you havent found the gold." << endl;
            cout << "You must continue" << "\n\n";
            return true;
        }
    }
    return true;
}

/***********************************************************************************
 ** Function: eventEncounter
 ** Description: encounters events
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
bool Map::eventEncounter(){
    bool arrowCheck = checkArrows();
    bool winCheck;
    if(arrowCheck == false){
        return false;
    }
    switch(game[adventurerXpos][adventurerYpos]->getSupposedEvent()){
        case 1:
            winCheck = ropeReadventurerYpos();
            if(winCheck == false){
                return false;
            }
            else if(winCheck == true){
                return true;
            }
            break;
        case 2:
            giveEntrance(game[adventurerXpos][adventurerYpos]->getSupposedEvent());//different things based on event
            return false;
            break;
        case 3:
            giveEntrance(game[adventurerXpos][adventurerYpos]->getSupposedEvent());
            goldFlag = true;
            game[adventurerXpos][adventurerYpos]->setSupposedEvent(0);
            game[adventurerXpos][adventurerYpos]->setRoomEventActual(0);
            return true;
            break;
        case 4:
            giveEntrance(game[adventurerXpos][adventurerYpos]->getSupposedEvent());
            return false;
            break;
        case 5:
            giveEntrance(game[adventurerXpos][adventurerYpos]->getSupposedEvent());;
            batMove();
            return true;
            break;
   }
   return true;
}

/***********************************************************************************
 ** Function: getWumpus
 ** Description: returns wumpus
 ** Parameters: NA
 ** Pre-condtitions: map
 ** Post-conditions: map events
 ***********************************************************************************/
bool Map::getWumpus(){
   return wumpusFlag;
}

Map::~Map(){

}