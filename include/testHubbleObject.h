#include "hubbleObject.h"

#include <iostream>

class testHubbleObject : public hubbleObject
{

public:
    testHubbleObject(errorDisplay *ed);
    ~testHubbleObject();

    void update(float dt);
    void draw();
    void drawDebug();

    void query();
};