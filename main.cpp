#include <iostream>
#include <stdio.h>

#include "/home/jay/raylib/src/raylib.h"
#include "display.hpp"
#include "pyHelper.hpp"
#include "weatherGetter.hpp"
#include "colors.h"

#include "faces.h"

int main() 
{
std::cout << FACE_ANNOYED << std::endl;
    weatherGetter weatherman;
    display disp;

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
        
        disp.update(GetFrameTime());
        weatherman.update(GetFrameTime());        

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(A_BLUE);

            disp.draw();
            weatherman.draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
