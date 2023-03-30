#ifndef BATS_H
#define BATS_H

#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "event.h"
#include <iomanip>
#include <iostream>


using namespace std;

class Bats : public Event{
   private:
       string percept;
       string gridEvent;
   public:
       Bats();
       string getEncounter();
       string getPercept();
       ~Bats();
};

#endif