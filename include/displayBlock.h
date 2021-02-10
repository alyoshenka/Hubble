// displays data on the screen

#include "raylib.h"

#include "colors.h"

class displayBlock
{
    // draw area outline
    virtual void drawDebug() = 0;

public:
    virtual void update(float dt) = 0;
    virtual void draw() = 0;
};
