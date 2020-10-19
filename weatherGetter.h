#pragma once

#include "pyHelper.hpp"
#include <iostream>

#include "os.h"
#if ON_RPI
	#include "/home/jay/raylib/src/raylib.h"
#else
	#include "raylib.h"
#endif

#include "colors.h"

class weatherGetter
{
	CppPyObject pModule;
	CppPyInstance* pyInstance;
    
    float weatherUpdateTime;
    float updateElapsedTime;
    float lastUpdateTime;

    std::string weather;
    std::string temperature;

public:

	weatherGetter();
	~weatherGetter();
	std::string getTemperature();
	std::string getWeather();
	void update(float frameTime);
	void draw();
};
