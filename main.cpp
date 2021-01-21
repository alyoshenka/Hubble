#include "os.h"

#if ON_RPI
    #include "/home/jay/raylib/src/raylib.h"
#else
    #include "raylib.h"
#endif

#include "display.h"
#include "pyHelper.hpp"
#include "weatherGetter.h"
#include "colors.h"
#include "sensor.h"
#include "commandListener.h"
#include "commandManager.h"
#include "faces.h"
#include "internetSpeed.h"

#include <iostream>


int main() 
{
    
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "hubble_v2.1");
    
    weatherGetter weatherman;
    sensorDisplay tempHumd;
    commandListener listener;
    display d(screenWidth, screenHeight);
    display* disp = &d;
    commandManager comManager(disp);
    internetSpeed iSpeed;
    
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
        iSpeed.update(frameTime);
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
            iSpeed.draw();
            
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
