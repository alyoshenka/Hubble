#include "commandManager.h"

commandManager::commandManager(display* d){
	dsp = d;
}

void commandManager::parseCommand(string line){
	// remove newline
	line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
	
	int f = line.find_first_of(' ');
	string com = line.substr(0, f);
	line = line.substr(f+1);
	
	if(com.compare("mood") == 0){moodCommand(line);}
}

void commandManager::moodCommand(string m){
	std::cout << "m: |" << m << "|" << std::endl;
	dsp->setMood(m);
}
