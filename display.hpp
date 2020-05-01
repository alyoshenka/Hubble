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
    const std::string facesDir = "../thirdparty/sans/";

    std::string timeString;
    mood currentMood;
    Texture2D faceTex;
    Vector2 facePos;

public:
	display() 
    { 
        timeString = "time";
	facePos.x = facePos.y = 320;

	currentMood = happy;
	/*
	std::string num = std::to_string((int)currentMood + 1);
        std::string fileName = facesDir + "sansf" + num + ".png";
        std::cout << fileName << std::endl;
	Image img = LoadImage(fileName.c_str());
        faceTex = LoadTextureFromImage(img);
	UnloadImage(img);
	* */
    }

	~display() { /* UnloadTexture(faceTex); */ }

    void setMood(mood newMood)
    {
        currentMood = newMood;
	/*
        UnloadTexture(faceTex); 
	std::string num = std::to_string((int)currentMood + 1);
        std::string fileName = facesDir + "sansf" + num + ".png";
        std::cout << fileName << std::endl;
        faceTex = LoadTexture(fileName.c_str());
	* */
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
	}
	
	void draw()
	{
		DrawText("HUBBLE", 10, 5, 80, A_BLUE_3);
		DrawText(FACE_AT, 320, 320, 160, A_BLUE_4);
		DrawText(timeString.c_str(), 640, 10, 40, A_GREEN_2);

		// DrawTexture(faceTex, facePos.x, facePos.y, WHITE);
	}
};

#endif
