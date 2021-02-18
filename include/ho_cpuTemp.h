#pragma once

#include "hubbleObject.h"

// CPU Temperature
class ho_cpuTemp : public hubbleObject
{
    string tempStr;
    
    float CtoF(float c);
    float toTempStr(float f);
public:
    ho_cpuTemp(errorDisplay *ed);
    ~ho_cpuTemp();

    void draw();
    void drawDebug();

    void query();
};
