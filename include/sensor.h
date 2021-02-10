#pragma once

#include <iostream>
#include <fstream>
#include <thread>

#include "pyHelper.hpp"
<<<<<<< HEAD:sensor.h
#include "os.h"
#include "errorDisplay.h"
=======
#include "config.h"
>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c:include/sensor.h

class dht22Query
{
	const std::string command = "particle call Medusa";
	const std::string temp = "temp";
	const std::string humd = "humd";

#if ON_RPI
	CppPyObject pModule;
	CppPyInstance *pyInstance;
#endif

#if ON_RPI
	std::thread query;
#endif

	int get(std::string file);
	static void queryThread();

public:
<<<<<<< HEAD:sensor.h
	errorDisplay* eDisp;
	
	dht22Query();	
	~dht22Query();	
	void queryData();	
	int getTemp();	
=======
	dht22Query();
	~dht22Query();
	void queryData();
	int getTemp();
>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c:include/sensor.h
	int getHumd();
};

#include "raylib.h"
#include "colors.h"

class sensorDisplay
{
	errorDisplay* eDisp;
	
	float sensorUpdateTime;
	float displayUpdateTime;
	float updateElapsedTime;
	float lastUpdateTime;
	bool shouldQuery;
<<<<<<< HEAD:sensor.h
    
	int temp, humd;
    
	dht22Query sensor;
    
public:
	sensorDisplay(errorDisplay* errDisp);	
=======

	int temp, humd;

	dht22Query sensor;

public:
	sensorDisplay();
>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c:include/sensor.h
	~sensorDisplay();
	void update(float frameTime);
	void draw();
};
