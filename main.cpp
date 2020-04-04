#include <iostream>
#include <stdio.h>

#include "/home/jay/raylib/src/raylib.h"
#include "pyHelper.hpp"
#include "weatherGetter.hpp"

int main() 
{
    weatherGetter weatherman;
    std::string weather = weatherman.getWeather();
    std::string temperature = weatherman.getTemperature() + "f";

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
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawText("HUBBLE", 100, 100, 150, RED);
            DrawText("(@_@)", 700, 440, 20, BLACK);
            DrawText("Seattle, WA", 50, 280, 60, BLUE);
            DrawText(weather.c_str(), 80, 350, 40, BLACK);
            DrawText(temperature.c_str(), 80, 400, 40, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
