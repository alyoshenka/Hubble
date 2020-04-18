#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#pragma warning(disable : 4996)
#include <ctime>
#include <string>

#include "os.h"
#if ON_RPI
    #include "/home/jay/raylib/src/raylib.h"
#else
    #include "raylib.h"
#endif

#include "colors.h"
#include "faces.h"

class display
{

    std::string timeString;

public:
	display() 
    { 
        timeString = "time";
    }

	~display() { }
	
	void update(float frameTime)
	{
        std::time_t now = time(0);
        tm* local = localtime(&now);

        int h = local->tm_hour;
        int m = local->tm_min;
        int s = local->tm_sec;

        timeString = "";
        if (h < 10) { timeString += "0"; }
        timeString += std::to_string(h) + ":";
        if (m < 10) { timeString += "0"; }
        timeString += std::to_string(m) + ":";
        if (s < 10) { timeString += "0"; }
        timeString += std::to_string(s);
	}
	
	void draw()
	{
		DrawText("HUBBLE", 10, 5, 80, A_PURPLE_3);
		DrawText(FACE_AT, 320, 320, 160, A_PURPLE_4);
		DrawText(timeString.c_str(), 640, 10, 40, A_GREEN_2);
	}
};

#endif
