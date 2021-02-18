#include "ho_weatherGetter.h"

ho_weatherGetter::ho_weatherGetter(errorDisplay *ed) : hubbleObject(ed)
{
#if ctor_debug
    std::cout << "ho_weatherGetter constructed" << std::endl;
#endif

    wthr = "weather string";
    temp = "00 *f";

    updateTime = 20 * 60; // 20 min
    updateElapsed = updateTime;
}

ho_weatherGetter::~ho_weatherGetter()
{
#if dtor_debug
    std::cout << "ho_weatherGetter destructed" << std::endl;
#endif
}

void ho_weatherGetter::query()
{
    eDisp->addErrString("ho_weatherGetter query");
    
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
    DrawRectangle(600, 0, 200, 120, YELLOW);
}
