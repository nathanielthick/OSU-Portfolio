#ifndef EVENT_H
#define EVENT_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>


using namespace std;

class Event {
   private:
       string percept;
       string gridEvent;
   public:
        Event& operator= (const Event &event);
       Event();
       virtual string getEncounter();
       virtual string getPercept();
       ~Event();
};

#endif