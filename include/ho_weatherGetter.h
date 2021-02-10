#include "hubbleObject.h"

class ho_weatherGetter : public hubbleObject
{
    string wthr;
    string temp;

public:
    ho_weatherGetter();
    ~ho_weatherGetter();

    void draw();
    void drawDebug();

    void query();
};