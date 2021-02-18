#include "ho_cpuTemp.h"

ho_cpuTemp::ho_cpuTemp(errorDisplay* ed) : hubbleObject(ed)
{
#if ctor_debug
	std::cout << "ho_cpuTemp constructed" << std::endl;
#endif

	tempStr = "99.9*C";
	updateTime = 1 * 60; // 1 min
	updateElapsed = updateTime;
}

ho_cpuTemp::~ho_cpuTemp()
{
#if dtor_debug
	std::cout << "ho_cpuTemp destructed" << std::endl;
#endif
}

void ho_cpuTemp::draw()
{
	DrawText("CPU temp", 610, 130, 30, A_BLUE_2);
	
	DrawText(tempStr.c_str(), 620, 165, 25, A_BLUE_1);
}

void ho_cpuTemp::drawDebug()
{
	DrawRectangle(600, 120, 200, 80, ORANGE);
}

void ho_cpuTemp::query()
{
	eDisp->addErrString("ho_cpuTemp query");
	
	string tempNew = getTerminalOutput(get_cpu_temp_full);
	if(validateData(tempNew))
	{
		int i = tempNew.find_first_of('=');
		tempNew = tempNew.substr(i+1);
		tempStr = tempNew;
	}
}
