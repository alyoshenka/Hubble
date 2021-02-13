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
    std::cout << "ho_weatherGetter query" << std::endl;
    
    string wthrNew = getTerminalOutput(get_weather_full);
    if(validateData(wthrNew)) { wthr = wthrNew; }
    string tempNew = getTerminalOutput(get_temperature_full);
    if(validateData(tempNew)) 
    { 
        tempNew.erase(std::remove(tempNew.begin(), tempNew.end(), '\n'), tempNew.end());
        temp = tempNew.append(" *f"); 
    }
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
