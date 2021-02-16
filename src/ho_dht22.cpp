#include "ho_dht22.h"

ho_dht22::ho_dht22(errorDisplay *ed) : hubbleObject(ed)
{
#if ctor_debug
	std::cout << "ho_dht22 constructed" << std::endl;
#endif
	temp = humd = 99.99;
	updateTime = 60 * 5; // 5 minutes
	updateElapsed = updateTime;
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
	
	DrawText("99*f", 620, 245, 25, A_BLUE_1);
	DrawText("99%h", 690, 245, 25, A_BLUE_1);
}

void ho_dht22::drawDebug()
{
	DrawRectangle(600, 200, 200, 80, RED);
}

void ho_dht22::query()
{
}
