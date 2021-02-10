#pragma once

#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <future>
#include <chrono>

#include "os.h"
#if ON_RPI
	#include "/home/jay/raylib/src/raylib.h"
#else
	#include "raylib.h"
#endif

#include "colors.h"
#include "errorDisplay.h"

#define WEATHERPI "weatherpi"
#define WEATHER " weather"
#define TEMPERATURE " temperature"

#using std::string;

class weatherGetter
{	
	errorDisplay* eDisp;
	
	std::future<void> fut;
    
    float updateTime, updateElapsed;

    string weather;
    string temperature;
    
    void updateViaThread();

public:

	weatherGetter(errorDisplay* errDisp);

	string getTemperature();
	string getWeather();
	void update(float frameTime);
	void draw();
};
