#include "hubbleObject.h"

#include <iostream>

hubbleObject::hubbleObject(errorDisplay *ed)
{
    std::cout << "hubbleObject constructed" << std::endl;

    eDisp = ed;

    updateTime = 5;
    updateElapsed = 0;
}

hubbleObject::~hubbleObject()
{
    eDisp = nullptr;
    std::cout << "hubbleObject destructed" << std::endl;
}

void hubbleObject::update(float dt)
{
    updateElapsed += dt;

    if (updateReady())
    {
        eDisp->addErrString("update tho");
        getTerminalOutput(basic_cmd);
        queryViaThread();
        resetUpdateTimer();
    }
}

bool hubbleObject::updateReady() { return updateElapsed >= updateTime; }

void hubbleObject::resetUpdateTimer() { updateElapsed = 0; }