#ifndef GOLD_H
#define GOLD_H

#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "event.h"

using namespace std;

class Gold : public Event {
   private:
       string gridEvent;
       string percept;
   public:
       Gold();
       string getEncounter();
       string getPercept();
       ~Gold();
};

#endif  