#include "hubbleObject.h"

#include <iostream>

class testHubbleObject : public hubbleObject
{

public:
    testHubbleObject();
    ~testHubbleObject();

    void update(float dt);
    void draw();
    void drawDebug();

    void query();
};