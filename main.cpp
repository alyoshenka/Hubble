#include "os.h"

#if ON_RPI
    #include "/home/jay/raylib/src/raylib.h"
#else
    #include "raylib.h"
#endif

#include "display.h"
#include "pyHelper.hpp"
#include "weatherGetter.hpp"
#include "colors.h"
#include "sensor.hpp"
#include "sensor.hpp"

#include "commandListener.h"
#include "commandManager.h"

#include "faces.h"

#include <iostream>

int main() 
{
    weatherGetter weatherman;
    sensorDisplay tempHumd;
    commandListener listener;

    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "hubble_v1");
    
    display d(screenWidth, screenHeight);
    display* disp = &d;
    commandManager comManager(disp);
    listener.sendListener();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        
        float frameTime = GetFrameTime();
        disp->update(frameTime);
        weatherman.update(frameTime);        
        tempHumd.update(frameTime);
        listener.listen();
        if(listener.newMessage()){
            comManager.parseCommand(listener.getMessage());
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(A_BLUE);

            disp->draw();
            weatherman.draw();
            tempHumd.draw();
            
            // string msg = listener.getMessage();
            // if(!msg.empty()) { std::cout << "msg: " << msg << std::endl; }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    listener.stopListener();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
