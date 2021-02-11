#include "ho_weatherGetter.h"

ho_weatherGetter::ho_weatherGetter(errorDisplay *ed) : hubbleObject(ed)
{
    std::cout << "ho_weatherGetter constructed" << std::endl;

    wthr = "weather string";
    temp = "00 *f";

    updateTime = 20 * 60; // 20 min
    updateElapsed = updateTime;
}

ho_weatherGetter::~ho_weatherGetter()
{
    std::cout << "ho_weatherGetter destructed" << std::endl;
}

void ho_weatherGetter::query()
{
    eDisp->addErrString("ho_weatherGetter query");
}

void ho_weatherGetter::draw()
{
    DrawText("Seattle, WA", 605, 15, 30, A_BLUE_2);
    DrawText(wthr.c_str(), 615, 50, 20, A_BLUE_1);
    DrawText(temp.c_str(), 615, 80, 20, A_BLUE_1);
}

void ho_weatherGetter::drawDebug()
{
    DrawRectangleLines(600, 0, 200, 105, PINK);
}