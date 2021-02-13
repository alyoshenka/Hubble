#include <algorithm> // erase

#include "hubbleObject.h"

class ho_weatherGetter : public hubbleObject
{
    string wthr, temp;
    string qWthr, qTemp; // query placeholders(?)

public:
    ho_weatherGetter(errorDisplay *ed);
    ~ho_weatherGetter();

    void draw();
    void drawDebug();

    void query();
};
