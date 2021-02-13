#include "config.h"

#if ON_RPI
#include "/home/jay/raylib/src/raylib.h"
#else
#include "C:/Users/asus/Desktop/thirdparty/raylib/3.5.0/x86/include/raylib.h" // not sure how to fix
#endif

#include "display.h"
#include "colors.h"
#include "sensor.h"
#include "commandListener.h"
#include "commandManager.h"
#include "faces.h"
#include "errorDisplay.h"

#include "ho_internetSpeed.h"
#include "ho_weatherGetter.h"

#include <iostream>


int main()
{
    std::cout << "starting" << std::endl;

    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "hubble_v2.1");

    errorDisplay *errorDisp = new errorDisplay(); 
    sensorDisplay tempHumd(errorDisp); 
    display d(screenWidth, screenHeight, errorDisp); 
    display *disp = &d; 
#if ON_RPI
    // commandListener listener(errorDisp);
    // commandManager comManager(disp, errorDisp);
    // listener.sendListener();
#endif

    ho_internetSpeed ho_is(errorDisp); 
    ho_weatherGetter ho_wg(errorDisp); 

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        float frameTime = GetFrameTime();
        disp->update(frameTime);
        tempHumd.update(frameTime);
#if ON_RPI
/*
        listener.listen();
        if (listener.newMessage())
        {
            comManager.parseCommand(listener.getMessage());
        }
        * */
#endif

        ho_is.update(frameTime);
        ho_wg.update(frameTime);

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------

        ClearBackground(A_BLUE);

        errorDisp->draw();

        ho_is.drawDebug();
        ho_is.draw();
        ho_wg.drawDebug();
        ho_wg.draw();

        disp->draw();
        tempHumd.draw();
        
        disp->drawLayoutDebug();

        // string msg = listener.getMessage();
        // if(!msg.empty()) { std::cout << "msg: " << msg << std::endl; }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

// De-Initialization
//--------------------------------------------------------------------------------------
#if ON_RPI
    // listener.stopListener();
#endif
    delete errorDisp;
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
