#include "ho_dht22.h"

ho_dht22::ho_dht22(errorDisplay *ed) : hubbleObject(ed)
{
#if ctor_debug
	std::cout << "ho_dht22 constructed" << std::endl;
#endif
	temp = humd = 99.99;
	updateTime = 60 * 5; // 5 minutes
	updateElapsed = updateTime; // delay?
	
	tempStr = "99*f";
	humdStr = "99%";
}

ho_dht22::~ho_dht22()
{
#if dtor_debug
	std::cout << "ho_dht22 destructed" << std::endl;
#endif
}

void ho_dht22::draw()
{
	DrawText("Photon", 610, 210, 30, A_BLUE_2);
	
	DrawText(tempStr.c_str(), 620, 245, 25, A_BLUE_1);
	DrawText(humdStr.c_str(), 690, 245, 25, A_BLUE_1);
}

void ho_dht22::drawDebug()
{
	DrawRectangle(600, 200, 200, 80, RED);
}

void ho_dht22::query()
{
	eDisp->addErrString("ho_dht22 query");
	
	// validate data
	
	string t = getTerminalOutput(particle_temp);
	if(validateData(t)) { tempStr = t.substr(0, 2) + "*f"; }
	string h = getTerminalOutput(particle_humd);
	if(validateData(h)){ humdStr = h.substr(0, 2) + "%"; }
}
