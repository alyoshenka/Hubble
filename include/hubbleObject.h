#pragma once

#include "config.h"
#include "commands.h"

#include "peripheral.h"
#include "displayBlock.h"

#include "errorDisplay.h"



#include <future> // std::future
#include <chrono> // chrono literals
#include <iostream> // output
#include <string> // string

using std::string;
using namespace std::chrono_literals;

// displays data from a peripheral
class hubbleObject : public peripheral, public displayBlock
{

    hubbleObject(); // enforce errorDisplay

protected:
    float updateTime, updateElapsed; // how often to update, time since last update, (s)
    errorDisplay *eDisp;
    
    static bool validateData(string data); // is given data valid? (len > 0)

public:
    hubbleObject(errorDisplay *ed);
    ~hubbleObject();

    void update(float dt);

    bool updateReady();      // updateTime > updateElapsed?
    void resetUpdateTimer(); // reset update timer to 0
};
