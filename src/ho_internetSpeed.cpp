#include "ho_internetSpeed.h"

ho_internetSpeed::ho_internetSpeed(errorDisplay *ed) : hubbleObject(ed)
{
#if ctor_debug
    std::cout << "ho_is constructor" << std::endl;
#endif

    dn = 199.99;
    up = 9.99;

    updateTime = 15 * 60; // min
    updateElapsed = updateTime;

    setSpeedStrings();
}

ho_internetSpeed::~ho_internetSpeed()
{
#if dtor_debug
    std::cout << "ho_is destructor" << std::endl;
#endif
}

void ho_internetSpeed::draw()
{
    DrawText("DWN:", 405, 405, 20, A_GREEN_2);
    DrawText("UP:", 260, 405, 20, A_GREEN_2);

    DrawText(dStr.c_str(), 460, 415, 40, A_BLUE_1);
    DrawText(uStr.c_str(), 300, 415, 40, A_BLUE_1);

    DrawText("Mbps", 460, 455, 15, A_GREEN_1);
    DrawText("Mbps", 300, 455, 15, A_GREEN_1);
}

void ho_internetSpeed::drawDebug()
{
    DrawRectangleLines(250, 400, 350, 80, PINK);
}

float ho_internetSpeed::speedStringToFloat(const string line)
{
#if periph_debug
    std::cout << line << ": ";
#endif periph_debug
    string l = string(line);
    int i = l.find_first_of(' ');
    l = l.substr(i + 1);
    i = l.find_first_of(' ');
    l = l.substr(0, i);

    return std::stof(l);
}

void ho_internetSpeed::query()
{
    eDisp->addErrString("ho_internetSpeed query");

    string upNew = getTerminalOutput(get_up_speed);
    if (validateData(upNew))
    {
        up = speedStringToFloat(upNew);
    }
    string dnNew = getTerminalOutput(get_dn_speed);
    if (validateData(dnNew))
    {
        dn = speedStringToFloat(dnNew);
    }

    setSpeedStrings();
}

void ho_internetSpeed::setSpeedStrings()
{
    std::stringstream uStream, dStream;
    uStream << std::fixed << std::setprecision(2) << up;
    dStream << std::fixed << std::setprecision(2) << dn;
    uStr = uStream.str();
    dStr = dStream.str();
}
