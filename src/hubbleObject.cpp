#include "hubbleObject.h"

#include <iostream>

hubbleObject::hubbleObject()
{
    std::cout << "hubbleObject constructed" << std::endl;

    updateTime = 5;
    updateElapsed = 0;
}

hubbleObject::~hubbleObject()
{
    std::cout << "hubbleObject destructed" << std::endl;
}

void hubbleObject::update(float dt)
{
    updateElapsed += dt;

    if (updateReady())
    {
        std::cout << "update tho" << std::endl;
        getTerminalOutput(basic_cmd);
        queryViaThread();
        resetUpdateTimer();
    }
}

bool hubbleObject::updateReady() { return updateElapsed >= updateTime; }

void hubbleObject::resetUpdateTimer() { updateElapsed = 0; }