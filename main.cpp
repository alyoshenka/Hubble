#include<iostream>
#include <stdio.h>

#include "/home/jay/raylib/src/raylib.h"
#include "pyHelper.hpp"

int main() 
{
    CppPyInstance pyInstance;

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('/home/jay/WeatherPi')");

    CppPyObject pName = PyUnicode_FromString("weather");
	CppPyObject pModule = PyImport_Import(pName);

	if (pModule)
	{
		CppPyObject pFunc = PyObject_GetAttrString(pModule, "get_weather");
		if (pFunc && PyCallable_Check(pFunc))
		{
			CppPyObject pValue = PyObject_CallObject(pFunc, NULL);
            if(pValue)
            {
			    printf("cpp: %s\n", _PyUnicode_AsString(pValue));
            }
            else { PyErr_Print(); }
		}
		else { printf("Error func: %d check: %d", pFunc, PyCallable_Check(pFunc)); }
	}
	else { PyErr_Print(); }
return 0;

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 480;

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
            DrawText("(@_@)", 200, 300, 100, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
