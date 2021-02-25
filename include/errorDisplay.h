#pragma once

#include "config.h"
#if ON_RPI
#include "/home/jay/raylib/src/raylib.h"
#else
#include "raylib.h"
#pragma warning(disable : 4996)
#endif

#include <string>
using std::string;

class errorDisplay // : public displayBlock
{
    const int dispNum = 14;
    int errStrCnt;
    int errStrIdx;
    string *errStrArr;

public:
    errorDisplay();
    ~errorDisplay();

    bool addErrString(string errString);
    void draw();
};
