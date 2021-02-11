#include "testHubbleObject.h"

testHubbleObject::testHubbleObject(errorDisplay *ed) : hubbleObject(ed)
{
    std::cout << "tho constructed" << std::endl;
}

testHubbleObject::~testHubbleObject()
{
    std::cout << "tho destructed" << std::endl;
}

void testHubbleObject::update(float dt)
{
    hubbleObject::update(dt);
    if (updateReady())
    {
        eDisp->addErrString("update tho");
        getTerminalOutput(basic_cmd);
        queryViaThread();
        resetUpdateTimer();
    }
}

void testHubbleObject::draw() { return; }

void testHubbleObject::drawDebug()
{
    DrawRectangle(100, 150, 200, 100, PINK);
}

void testHubbleObject::query()
{
    eDisp->addErrString("tho query func");
}