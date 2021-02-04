#include "weatherGetter.h"

weatherGetter::weatherGetter()
{
	weatherUpdateTime = 60 * 10;
	updateElapsedTime = lastUpdateTime = 0;

#if ON_RPI
	pyInstance = new CppPyInstance();

	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('/home/jay/WeatherPi')");

	CppPyObject pName = PyUnicode_FromString("weather");
	pModule = PyImport_Import(pName);

	if (!pModule)
	{
		PyErr_Print();
	}
#endif

	getWeather();
	getTemperature();
}

weatherGetter::~weatherGetter()
{
#if ON_RPI
	pyInstance = nullptr;
#endif
}

std::string weatherGetter::getTemperature()
{
	std::string ret = "0";
#if not ON_RPI
	temperature = ret + "°f";
	return ret;
#endif

#if ON_RPI
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
		else
		{
			PyErr_Print();
		}
	}
	else
	{
		PyErr_Print();
	}

	return ret;
#endif

	return ret;
}

std::string weatherGetter::getWeather()
{
	std::string ret = "weather";
#if not ON_RPI
	weather = ret;
	return ret;
#endif

#if ON_RPI
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
		else
		{
			PyErr_Print();
		}
	}
	else
	{
		PyErr_Print();
	}

	return ret;
#endif

	return ret;
}

void weatherGetter::update(float frameTime)
{
	updateElapsedTime += frameTime;
	lastUpdateTime += frameTime;

	if (updateElapsedTime > weatherUpdateTime)
	{
		updateElapsedTime = 0;
		getWeather();
		getTemperature();
	}
}

void weatherGetter::draw()
{
	DrawText("Seattle, WA", 605, 15, 30, A_BLUE_2);
	DrawText(weather.c_str(), 615, 50, 20, A_BLUE_1);
	DrawText(temperature.c_str(), 615, 80, 20, A_BLUE_1);

	// std::string updateStr = "Updated " + std::to_string((int)(lastUpdateTime / 60) + 1) + " mins ago";
	// DrawText(updateStr.c_str(), 615, 105, 10, A_GREEN_2);
}
