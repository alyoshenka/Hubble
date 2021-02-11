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

int main()
{
    std::cout << "starting" << std::endl;

    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "hubble_v2.1");

    errorDisplay *errorDisp = new errorDisplay();

    weatherGetter weatherman(errorDisp);
    sensorDisplay tempHumd(errorDisp);
    display d(screenWidth, screenHeight, errorDisp);
    display *disp = &d;
    internetSpeed iSpeed(errorDisp);
#if ON_RPI
    // commandListener listener(errorDisp);
    // commandManager comManager(disp, errorDisp);
#endif

    // testHubbleObject tho(errorDisp);
    ho_internetSpeed ho_is(errorDisp);
    ho_weatherGetter ho_wg(errorDisp);

#if ON_RPI
    // listener.sendListener();
#endif

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
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

        errorDisp->draw();
        disp->drawLayoutDebug();

        // tho.drawDebug();
        ho_is.drawDebug();
        ho_is.draw();
        ho_wg.drawDebug();
        ho_wg.draw();

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
#if ON_RPI
    // listener.stopListener();
#endif
    delete errorDisp;
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
