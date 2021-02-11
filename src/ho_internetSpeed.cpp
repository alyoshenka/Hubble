#include "ho_internetSpeed.h"

ho_internetSpeed::ho_internetSpeed(errorDisplay *ed) : hubbleObject(ed)
{
    std::cout << "ho_is constructor" << std::endl;

    dn = 199.99;
    up = 9.99;

    updateTime = 15 * 60; // min
    updateElapsed = updateTime;

    setSpeedStrings();
}

ho_internetSpeed::~ho_internetSpeed()
{
    std::cout << "ho_is destructor" << std::endl;
}

void ho_internetSpeed::draw()
{
    DrawText("DWN:", 405, 305, 20, A_GREEN_2);
    DrawText("UP:", 260, 305, 20, A_GREEN_2);

    DrawText(dStr.c_str(), 460, 315, 40, A_BLUE_1);
    DrawText(uStr.c_str(), 300, 315, 40, A_BLUE_1);

    DrawText("Mbps", 460, 355, 15, A_GREEN_1);
    DrawText("Mbps", 300, 355, 15, A_GREEN_1);
}

void ho_internetSpeed::drawDebug()
{
    DrawRectangleLines(250, 400, 350, 80, PINK);
}

void ho_internetSpeed::query()
{
    eDisp->addErrString("query internet speed");
}

void ho_internetSpeed::setSpeedStrings()
{
    std::stringstream uStream, dStream;
    uStream << std::fixed << std::setprecision(2) << up;
    dStream << std::fixed << std::setprecision(2) << dn;
    uStr = uStream.str();
    dStr = dStream.str();
}
