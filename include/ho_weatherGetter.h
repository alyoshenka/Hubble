#pragma once

#include <algorithm> // erase

#include "hubbleObject.h"

class ho_weatherGetter : public hubbleObject
{
    string wthr, temp;

public:
    ho_weatherGetter(errorDisplay *ed);
    ~ho_weatherGetter();

    void draw();
    void drawDebug();

    void query();
};
