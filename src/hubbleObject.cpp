#include "hubbleObject.h"

#include <iostream>

hubbleObject::hubbleObject(errorDisplay *ed)
{
    std::cout << "hubbleObject constructed" << std::endl;

    eDisp = ed;

    updateTime = 5;
    updateElapsed = 0;
}

hubbleObject::~hubbleObject()
{
    eDisp = nullptr;
    std::cout << "hubbleObject destructed" << std::endl;
}

bool hubbleObject::validateData(string data) { return data.length() > 0; }

void hubbleObject::update(float dt)
{
    updateElapsed += dt;

    if (updateReady())
    {
        eDisp->addErrString("update tho");
        getTerminalOutput(basic_cmd);
        queryViaThread();
        resetUpdateTimer();
    }
    
#if ON_RPI
    if (fut.valid())
    {
        // is this ok?
        // eDisp->addErrString("fut valid");
        try
		{
			std::future_status s = fut.wait_for(0ms);
			if (std::future_status::ready == s)
			{
				fut.get();

				eDisp->addErrString("recieved peripheral data");
			}
		}
		catch (const std::future_error &e)
		{
			std::cerr << "future error: " << e.code() << std::endl;
			eDisp->addErrString("future error");
		}
        
    }
#endif
}

bool hubbleObject::updateReady() { return updateElapsed >= updateTime; }

void hubbleObject::resetUpdateTimer() { updateElapsed = 0; }
