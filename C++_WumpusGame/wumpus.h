#ifndef WUMPUS_H
#define WUMPUS_H

#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "event.h"

using namespace std;

class Wumpus : public Event {
   private:
       string percept;
       string gridEvent;
   public:
       Wumpus();
       string getEncounter();
       string getPercept();
       ~Wumpus();
};

#endif