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

#include "testHubbleObject.h"
#include "ho_internetSpeed.h"
#include "ho_weatherGetter.h"

#include <iostream>

int main()
{
    testHubbleObject tho;
    ho_internetSpeed ho_is;
    ho_weatherGetter ho_wg;

    std::cout << "boop" << std::endl;
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "hubble_v2.1");

    weatherGetter weatherman;
    sensorDisplay tempHumd;
    commandListener listener;
    display d(screenWidth, screenHeight);
    display *disp = &d;
    commandManager comManager(disp);
    internetSpeed iSpeed;

    listener.sendListener();

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
        listener.listen();
        if (listener.newMessage())
        {
            comManager.parseCommand(listener.getMessage());
        }

        tho.update(frameTime);
        ho_is.update(frameTime);
        ho_wg.update(frameTime);

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(A_BLUE);

        disp->drawLayoutDebug();

        tho.drawDebug();
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
    listener.stopListener();
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
