#include "config.h"

#if ON_RPI
#include "/home/jay/raylib/src/raylib.h"
#else
#include "C:/Users/asus/Desktop/thirdparty/raylib/3.5.0/x86/include/raylib.h" // not sure how to fix
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
#include "errorDisplay.h"

#include <iostream>

int main()
{
    std::cout << "boop" << std::endl;
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "hubble_v2.1");
<<<<<<< HEAD
    
    errorDisplay* errorDisp = new errorDisplay();  
    weatherGetter weatherman(errorDisp); 
    sensorDisplay tempHumd(errorDisp); 
    commandListener listener(errorDisp); 
    display d(screenWidth, screenHeight, errorDisp); 
    display* disp = &d; 
    commandManager comManager(disp, errorDisp); 
    internetSpeed iSpeed(errorDisp); 
    
    
    listener.sendListener(); std::cout << "sl" << std::endl;
    
    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
=======

    weatherGetter weatherman;
    sensorDisplay tempHumd;
    commandListener listener;
    display d(screenWidth, screenHeight);
    display *disp = &d;
    commandManager comManager(disp);
    internetSpeed iSpeed;

    listener.sendListener();

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        float frameTime = GetFrameTime();
        disp->update(frameTime);
        weatherman.update(frameTime);
        tempHumd.update(frameTime);
        iSpeed.update(frameTime);
        listener.listen();
        if (listener.newMessage())
        {
            comManager.parseCommand(listener.getMessage());
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        

<<<<<<< HEAD
        BeginDrawing();
    
            ClearBackground(A_BLUE);

            disp->draw();
            weatherman.draw();
            tempHumd.draw();
            iSpeed.draw();
            errorDisp->draw();
            
            // string msg = listener.getMessage();
            // if(!msg.empty()) { std::cout << "msg: " << msg << std::endl; }
=======
        ClearBackground(A_BLUE);

        disp->draw();
        weatherman.draw();
        tempHumd.draw();
        iSpeed.draw();

        // string msg = listener.getMessage();
        // if(!msg.empty()) { std::cout << "msg: " << msg << std::endl; }
>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    listener.stopListener();
<<<<<<< HEAD
    delete errorDisp;  
    CloseWindow();        // Close window and OpenGL context
=======
    CloseWindow(); // Close window and OpenGL context
>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c
    //--------------------------------------------------------------------------------------

    return 0;
}
