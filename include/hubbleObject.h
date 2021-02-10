#pragma once

#include "peripheral.h"
#include "displayBlock.h"

#include "commands.h"

#include <iostream>
#include <string>
using std::string;

// displays data from a peripheral
class hubbleObject : public peripheral, public displayBlock
{
#if ON_RPI
    std::future<void> fut;
#endif

protected:
    float updateTime, updateElapsed; // how often to update, time since last update, (s)
public:
    hubbleObject();
    ~hubbleObject();

    void update(float dt);

    bool updateReady();      // updateTime > updateElapsed?
    void resetUpdateTimer(); // reset update timer to 0
};
