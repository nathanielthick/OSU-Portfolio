#ifndef PIT_H
#define PIT_H

#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "event.h"

class Pit : public Event{
   private:
       string percept;
       string gridEvent;
   public:
       Pit();
       string getEncounter();
       string getPercept();
       ~Pit();
};

#endif