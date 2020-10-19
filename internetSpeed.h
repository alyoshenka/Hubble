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

using std::string;
using std::thread;

using namespace std::chrono_literals;


// static?
class internetSpeed{
	
	float up, down;
	string uStr, dStr;
	float updateTime, updateElapsed;
	std::future<void> fut;
	
	string getCommand(string cmd);
	float getFloatFromSpeed(const string line); // 0.00f
	
public:
	internetSpeed();
	string getUpString();
	string getDownString();
	void testUp(); // queries upload speed, sets up
	void testDown(); // queries download speed, sets down
	float getUp();
	float getDown();
	void setStr();
	
	void updateViaThread();
	void update(float dt);
	void draw();
};


