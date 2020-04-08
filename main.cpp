#include <iostream>
#include <stdio.h>

#include "/home/jay/raylib/src/raylib.h"
#include "display.hpp"
#include "pyHelper.hpp"
#include "weatherGetter.hpp"
#include "colors.h"
#include "tank.hpp"

#include "faces.h"

int main() 
{
    weatherGetter weatherman;
    display disp;
    tank tub;

    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 480;

    HideCursor();

    InitWindow(screenWidth, screenHeight, "hubble_v1");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        
        float frameTime = GetFrameTime();
        disp.update(frameTime);
        weatherman.update(frameTime);        
        tub.update(frameTime);

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(A_BLUE);

            disp.draw();
            weatherman.draw();
            tub.draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
