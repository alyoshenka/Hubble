#pragma once

#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <future>
#include <chrono>

#define GET_UP_CMD "speedtest | grep Upload"
#define GET_DOWN_CMD "speedtest | grep Download"

#include "raylib.h"
#include "colors.h"
#include "errorDisplay.h"

using std::string;
#if ON_RPI
using std::thread;
#endif

using namespace std::chrono_literals;

// static?
<<<<<<< HEAD:internetSpeed.h
class internetSpeed{
	
	errorDisplay* eDisp;
	Font fnt;
	
	float up, down; // up/down load speeds (float)
	string uStr, dStr; // up/down load speeds (string)
=======
class internetSpeed
{

	float up, down;
	string uStr, dStr;
>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c:include/internetSpeed.h
	float updateTime, updateElapsed;
#if ON_RPI
	std::future<void> fut;
<<<<<<< HEAD:internetSpeed.h
	
	string getCommand(string cmd); // get output of cmd on command line
=======
#endif

	string getCommand(string cmd);
>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c:include/internetSpeed.h
	float getFloatFromSpeed(const string line); // 0.00f

public:
	internetSpeed(errorDisplay* errorDisp);
	
	string getUpString();
	string getDownString();
	void testUp();	 // queries upload speed, sets up
	void testDown(); // queries download speed, sets down
	float getUp();
	float getDown();
	void setStr();

	void updateViaThread();
	void update(float dt);
	void draw();
};
