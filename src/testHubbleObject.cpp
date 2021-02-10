#include "testHubbleObject.h"

testHubbleObject::testHubbleObject() : hubbleObject()
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
        std::cout << "update tho" << std::endl;
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
    std::cout << "tho query func" << std::endl;
}