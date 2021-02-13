#include "config.h"

#if ON_RPI
#include "/home/jay/raylib/src/raylib.h"
#else
#include "C:/Users/asus/Desktop/thirdparty/raylib/3.5.0/x86/include/raylib.h" // not sure how to fix
#endif

#include "display.h"
#include "weatherGetter.h"
#include "colors.h"
#include "sensor.h"
#include "commandListener.h"
#include "commandManager.h"
#include "faces.h"
#include "internetSpeed.h"
#include "errorDisplay.h"

#include "testHubbleObject.h"
#include "ho_internetSpeed.h"
#include "ho_weatherGetter.h"

#include <iostream>

#define ctor_debug true

int main()
{
    std::cout << "starting" << std::endl;

    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "hubble_v2.1");

    errorDisplay *errorDisp = new errorDisplay(); 
    #if ctor_debug 
    std::cout << "ed" << std::endl; 
    #endif

    weatherGetter weatherman(errorDisp); 
    #if ctor_debug 
    std::cout << "wm" << std::endl; 
    #endif
    sensorDisplay tempHumd(errorDisp); 
    #if ctor_debug 
    std::cout << "th" << std::endl; 
    #endif
    display d(screenWidth, screenHeight, errorDisp); 
    #if ctor_debug 
    std::cout << "d" << std::endl; 
    #endif
    display *disp = &d; 
    #if ctor_debug 
    std::cout << "ds" << std::endl; 
    #endif
    internetSpeed iSpeed(errorDisp); 
    #if ctor_debug 
    std::cout << "is" << std::endl; 
    #endif
#if ON_RPI
    // commandListener listener(errorDisp);
    // commandManager comManager(disp, errorDisp);
    // listener.sendListener();
#endif

    // testHubbleObject tho(errorDisp);
    ho_internetSpeed ho_is(errorDisp); 
    #if ctor_debug 
    std::cout << "his" << std::endl; 
    #endif
    ho_weatherGetter ho_wg(errorDisp); 
    #if ctor_debug 
    std::cout << "hwg" << std::endl; 
    #endif
    
    std::cout << "loop";

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        float frameTime = GetFrameTime();
        disp->update(frameTime);
        // weatherman.update(frameTime);
        tempHumd.update(frameTime);
        iSpeed.update(frameTime);
#if ON_RPI
/*
        listener.listen();
        if (listener.newMessage())
        {
            comManager.parseCommand(listener.getMessage());
        }
        * */
#endif

        // tho.update(frameTime);
        ho_is.update(frameTime);
        ho_wg.update(frameTime);

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------

        ClearBackground(A_BLUE);

        

        // tho.drawDebug();
        ho_is.drawDebug();
        ho_is.draw();
        ho_wg.drawDebug();
        ho_wg.draw();

        disp->draw();
        // weatherman.draw();
        tempHumd.draw();
        iSpeed.draw();
        
        errorDisp->draw();
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
