#include "config.h"

#if ON_RPI
#include "/home/jay/raylib/src/raylib.h"
#else
#include "C:/Users/asus/Desktop/thirdparty/raylib/3.5.0/x86/include/raylib.h" // not sure how to fix
#endif

#include "display.h"
#include "colors.h"
#include "commandListener.h"
#include "commandManager.h"
#include "faces.h"
#include "errorDisplay.h"

#include "ho_internetSpeed.h"
#include "ho_weatherGetter.h"
#include "ho_cpuTemp.h"
#include "ho_dht22.h"

#include <iostream>



int main()
{
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "hubble_v2.1");

    errorDisplay *errorDisp = new errorDisplay(); 
    display d(screenWidth, screenHeight, errorDisp); 
    display *disp = &d; 
#if ON_RPI
    // commandListener listener(errorDisp);
    // commandManager comManager(disp, errorDisp);
    // listener.sendListener();
#endif

    ho_internetSpeed ho_is(errorDisp); 
    ho_weatherGetter ho_wg(errorDisp); 
    ho_cpuTemp ho_ct(errorDisp);
    ho_dht22 ho_dh(errorDisp);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        float frameTime = GetFrameTime();
        disp->update(frameTime);
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
        ho_ct.update(frameTime);
        ho_dh.update(frameTime);

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------

        ClearBackground(A_BLUE);

        errorDisp->draw();

#if draw_debug
        ho_is.drawDebug();
        ho_wg.drawDebug();
        ho_ct.drawDebug();
        ho_dh.drawDebug();
        
        disp->drawLayoutDebug();
#endif
        
        ho_is.draw();
        ho_wg.draw();
        ho_ct.draw();
        ho_dh.draw();

        disp->draw();           
        

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
