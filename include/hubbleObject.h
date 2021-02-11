#pragma once

#include "peripheral.h"
#include "displayBlock.h"

#include "errorDisplay.h"

#include "commands.h"

#include <future> // std::future
#include <chrono> // chrono literals
#include <iostream> // output
#include <string> // string

using std::string;
using namespace std::chrono_literals;

// displays data from a peripheral
class hubbleObject : public peripheral, public displayBlock
{
#if ON_RPI
    std::future<void> fut;
#endif

    hubbleObject(); // enforce errorDisplay

protected:
    float updateTime, updateElapsed; // how often to update, time since last update, (s)
    errorDisplay *eDisp;

public:
    hubbleObject(errorDisplay *ed);
    ~hubbleObject();

    void update(float dt);

    bool updateReady();      // updateTime > updateElapsed?
    void resetUpdateTimer(); // reset update timer to 0
};
