#pragma once

#include <iostream>
#include <fstream>
#include <thread>

#include "config.h"
#include "errorDisplay.h"

class dht22Query
{
	const std::string command = "particle call Medusa";
	const std::string temp = "temp";
	const std::string humd = "humd";

#if ON_RPI
	std::thread query;
#endif

	int get(std::string file);
	static void queryThread();

public:
	errorDisplay *eDisp;

	dht22Query();
	~dht22Query();
	void queryData();
	int getTemp();
	int getHumd();
};

#include "raylib.h"
#include "colors.h"

class sensorDisplay
{
	errorDisplay *eDisp;

	float sensorUpdateTime;
	float displayUpdateTime;
	float updateElapsedTime;
	float lastUpdateTime;
	bool shouldQuery;

	int temp, humd;

	dht22Query sensor;

public:
	sensorDisplay(errorDisplay *errDisp);
	~sensorDisplay();
	void update(float frameTime);
	void draw();
};
