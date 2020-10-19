#pragma once

#include <ctime>
#include <string>
#include <algorithm>

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

using std::string;


enum mood
{
    happy,
    posessed,
    soulless,
    lookEyeDown,
    lookEyeUp,
    wink,
    veryNervous,
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

const string stringMood[16] = {
	"happy", 
	"posessed",
	"soulless",
	"lookEyeDown",
	"lookEyeUp",
	"wink",
	"veryNervous",
	"nervous",
	"peaceful",
	"sad",
	"vengeful",
	"scared",
	"dying",
	"pissed",
	"amused",
	"gone"
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
	display(int w, int h) ;
	~display();
	void setMood(mood newMood);
	void setMood(string newMood);	
	void setMood(int newMood);	
	void update(float frameTime);
	void draw();
};

