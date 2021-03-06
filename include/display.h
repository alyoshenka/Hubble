#pragma once

#include <ctime>
#include <string>
#include <algorithm>

#include "config.h"
#if ON_RPI
#include "/home/jay/raylib/src/raylib.h"
#else
#include "raylib.h"
#pragma warning(disable : 4996)
#endif

#include "displayBlock.h"
#include "colors.h"
#include "faces.h"
#include "errorDisplay.h"

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
    "gone"};

class display // : public displayBlock
{
// hardcoded to work on startup
#if ON_RPI
    const std::string facesDir = "/home/jay/Hubble/thirdparty/sans/";
#else
    const std::string facesDir = "C:/Users/asus/Desktop/Projects/Hubble/thirdparty/sans/"; // BAD!
#endif

    Font fnt;

    std::string timeString;
    mood currentMood;
    Texture2D faceTex;
    Vector2 facePos;
    int faceSize, faceBorder;
    errorDisplay *eDisp;

public:
    display(int w, int h, errorDisplay *errorDisp);
    ~display();
    void setMood(mood newMood);
    void setMood(string newMood);
    void setMood(int newMood);
    void update(float frameTime);
    void draw();
    void drawLayoutDebug();
};
