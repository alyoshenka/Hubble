#pragma once

#include <string>

#include <iostream>

#include "display.h"

using std::string;


class commandManager{
	display* dsp;
	
public:
	commandManager(display* d);
	void parseCommand(string line);
	void moodCommand(string m);
};
