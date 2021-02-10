#pragma once

#include <string>

#include <iostream>

#include "display.h"
#include "errorDisplay.h"

using std::string;


class commandManager{
	display* dsp;
	errorDisplay* eDisp; // doesn't really use it (yet)
	
public:
	commandManager(display* d, errorDisplay* errDisp);
	void parseCommand(string line);
	void moodCommand(string m);
};
