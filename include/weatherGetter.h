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
#include "pyHelper.hpp"
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
	CppPyObject pModule;
	CppPyInstance *pyInstance;
#endif

	float weatherUpdateTime;
	float updateElapsedTime;
	float lastUpdateTime;

	errorDisplay *eDisp;

	std::future<void> fut;

	float updateTime, updateElapsed;

	string weather;
	string temperature;

	void updateViaThread();

	std::string weather;
	std::string temperature;

	weatherGetter(errorDisplay *errDisp);

	string getTemperature();
	string getWeather();
	void update(float frameTime);
	void draw();
};
