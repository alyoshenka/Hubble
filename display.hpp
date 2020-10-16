#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <ctime>
#include <string>

#include "os.h"
#if ON_RPI
    #include "/home/jay/raylib/src/raylib.h"
#else
    #include "raylib.h"
    #pragma warning(disable : 4996)
#endif

#include "colors.h"
#include "faces.h"

#include <iostream>


enum mood
{
    happy,
    posessed,
    soulless,
    lookEyeDown,
    lookEyeUp,
    wink,
    veryNervouos,
    nervous,
    peaceful,
    sad,
    vengeful,
    scared,
    dying,
    pissed,
    amused,
    gone
};

class display
{
    // hardcoded to work on startup
    const std::string facesDir = "/home/jay/Hubble/thirdparty/sans/";

    std::string timeString;
    mood currentMood;
    Texture2D faceTex;
    Vector2 facePos;
    int faceSize, faceBorder;

public:
	display(int w, int h) 
    { 
        timeString = "time";
	faceSize = 200;
	faceBorder = 15;
    	facePos.x = w - faceSize - faceBorder;
	facePos.y = h - faceSize - faceBorder;	

	setMood(happy);
    }

	~display() { UnloadTexture(faceTex); }

    void setMood(mood newMood)
    {
        currentMood = newMood;
        UnloadTexture(faceTex); 
	std::string num = std::to_string((int)currentMood + 1);
        std::string fileName = facesDir + "sansf" + num + ".png";
        Image img = LoadImage(fileName.c_str());
	ImageResize(&img, faceSize, faceSize);
        faceTex = LoadTextureFromImage(img);
    	UnloadImage(img);
    }
	
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
		
		if(IsKeyPressed(KEY_W)){setMood(wink);}
		if(IsKeyPressed(KEY_H)){setMood(happy);}
	}
	
	void draw()
	{
		DrawText("HUBBLE", 10, 5, 80, A_BLUE_3);
		// DrawText(FACE_AT, 320, 320, 160, A_BLUE_4);
		DrawText(timeString.c_str(), 640, 10, 40, A_GREEN_2);

		DrawTexture(faceTex, facePos.x, facePos.y, WHITE);
	}
};

#endif
