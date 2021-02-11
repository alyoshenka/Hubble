#pragma once

#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <future>
#include <chrono>

#include "config.h"
#if ON_RPI
#include "/home/jay/raylib/src/raylib.h"
using namespace std::chrono_literals;
#else
#include "raylib.h"
#endif

#include "colors.h"
#include "errorDisplay.h"

#define WEATHERPI "weatherpi"
#define WEATHER " weather"
#define TEMPERATURE " temperature"

using std::string;

class weatherGetter
{
#if ON_RPI
	std::future<void> fut;
#endif

	errorDisplay *eDisp;

	float updateTime, updateElapsed;

	string weather;	
	string temperature;

	void updateViaThread();

public:
	weatherGetter(errorDisplay *errDisp);

	string getTemperature();
	string getWeather();
	void update(float frameTime);
	void draw();
};
