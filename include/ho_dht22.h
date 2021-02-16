#pragma once

#include "hubbleObject.h"

class ho_dht22 : public hubbleObject
{
	float temp, humd;
	
public:	
	ho_dht22(errorDisplay *ed);
	~ho_dht22();
	
	void draw();
    void drawDebug();

    void query();
};
