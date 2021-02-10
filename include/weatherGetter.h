#pragma once

#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <future>
#include <chrono>

#include "config.h"
#if ON_RPI
<<<<<<< HEAD:weatherGetter.h
	#include "/home/jay/raylib/src/raylib.h"
	#include "pyHelper.hpp"
	using namespace std::chrono_literals;
=======
#include "/home/jay/raylib/src/raylib.h"
>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c:include/weatherGetter.h
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
<<<<<<< HEAD:weatherGetter.h
{	
=======
{
>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c:include/weatherGetter.h
#if ON_RPI
	CppPyObject pModule;
	CppPyInstance *pyInstance;
#endif
<<<<<<< HEAD:weatherGetter.h

	float weatherUpdateTime;
	float updateElapsedTime;
	float lastUpdateTime;
	
	errorDisplay* eDisp;
	
	std::future<void> fut;
    
    float updateTime, updateElapsed;

    string weather;
    string temperature;
    
    void updateViaThread();
=======

	float weatherUpdateTime;
	float updateElapsedTime;
	float lastUpdateTime;
>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c:include/weatherGetter.h

	std::string weather;
	std::string temperature;

<<<<<<< HEAD:weatherGetter.h
	weatherGetter(errorDisplay* errDisp);

	string getTemperature();
	string getWeather();
=======
public:
	weatherGetter();
	~weatherGetter();
	std::string getTemperature();
	std::string getWeather();
>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c:include/weatherGetter.h
	void update(float frameTime);
	void draw();
};
