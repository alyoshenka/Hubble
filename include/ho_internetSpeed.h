#pragma once

#include <sstream> // stringstream
#include <iomanip> // setprecision

#include "hubbleObject.h"

#include <iostream>

class ho_internetSpeed : public hubbleObject
{
    float up, dn;      // up and down speeds
    string uStr, dStr; // speeds as formatted strings

    // converts speed to a float
    float speedStringToFloat(const string line); // 0.00f
    // sets display strings to precision
    void setSpeedStrings();

public:
    ho_internetSpeed(errorDisplay *ed);
    ~ho_internetSpeed();

    void draw();
    void drawDebug();

    void query();
};