#include "weatherGetter.h"

weatherGetter::weatherGetter(errorDisplay* errDisp)
{
	eDisp = errDisp;
	weatherUpdateTime = 60 * 10;

	getWeather();
	getTemperature();
}

std::string weatherGetter::getTemperature()
{
	std::string ret = "0";
	return ret;
#if not ON_RPI
	temperature = ret + "°f";
	return ret;
#endif

	CppPyObject pFunc = PyObject_GetAttrString(pModule, "get_temperature");
	if (pFunc && PyCallable_Check(pFunc))
	{
		CppPyObject pValue = PyObject_CallObject(pFunc, NULL);
		if (pValue)
		{
			ret = _PyUnicode_AsString(pValue);
			ret = ret.substr(0, 2) + "°f";
			temperature = ret;
			lastUpdateTime = 0;
		}
		else { PyErr_Print(); }
	}
	else { PyErr_Print(); }

	return ret;
}

std::string weatherGetter::getWeather()
{		
	std::string ret = "weather";
	return ret;
	#if not ON_RPI
		weather = ret;
		return ret;
	#endif

	CppPyObject pFunc = PyObject_GetAttrString(pModule, "get_weather");
	if (pFunc)
	{
		CppPyObject pValue = PyObject_CallObject(pFunc, NULL);
		if (pValue)
		{
			ret = _PyUnicode_AsString(pValue);
			weather = ret;
			lastUpdateTime = 0;
		}
		else { PyErr_Print(); }
	}
	else { PyErr_Print(); }

	return ret;
}

void weatherGetter::update(float dt)
{
	if(fut.valid()){
		try{
			std::future_status s = fut.wait_for(0ms);
			if(std::future_status::ready == s){
				fut.get();
				
				eDisp->addErrString("recieved new weather data");
			}
		}
		catch(const std::future_error& e){
			std::cerr << "future error: " << e.code() << std::endl;
			eDisp->addErrString("future error");
		}
	}	
	
	updateElapsed += dt;
	if(updateElapsed >= updateTime) { 
		updateElapsed = 0;
		updateViaThread(); 
	}
}

void weatherGetter::updateViaThread(){
	std::cout << "sending speed test async update" << std::endl;
	eDisp->addErrString("sending speedtest async update");
	
	fut = std::async(std::launch::async, [this]{
		this->getWeather();
	});
}

void weatherGetter::draw()
{
	DrawText("Seattle, WA", 605, 15, 30, A_BLUE_2);
	DrawText(weather.c_str(), 615, 50, 20, A_BLUE_1);
	DrawText(temperature.c_str(), 615, 80, 20, A_BLUE_1);
	
	// std::string updateStr = "Updated " + std::to_string((int)(lastUpdateTime / 60) + 1) + " mins ago";
	// DrawText(updateStr.c_str(), 615, 105, 10, A_GREEN_2);
}

