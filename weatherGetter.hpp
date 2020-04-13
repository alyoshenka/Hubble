#ifndef WEATHERGETTER_HPP
#define WEATHERGETTER_HPP
#pragma once

#include "pyHelper.hpp"
#include <iostream>

#include "/home/jay/raylib/src/raylib.h"
#include "colors.h"

class weatherGetter
{
	CppPyObject pModule;
	CppPyInstance* pyInstance;
    
    float weatherUpdateTime;
    float updateElapsedTime;
    float lastUpdateTime;

    std::string weather;
    std::string temperature;

public:

	weatherGetter()
	{
        weatherUpdateTime = 60 * 10;
        updateElapsedTime = lastUpdateTime = 0;

        pyInstance = new CppPyInstance();

		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.path.append('/home/jay/WeatherPi')");

		CppPyObject pName = PyUnicode_FromString("weather");
		pModule = PyImport_Import(pName);

		if (!pModule) { PyErr_Print(); }

        getWeather();
        getTemperature();
	}

	~weatherGetter()
    {
        pyInstance = nullptr;
    }

	std::string getTemperature()
	{
		std::string ret = "temperature";

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

	std::string getWeather()
	{
		std::string ret = "weather";

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

    void update(float frameTime)
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

	void draw()
	{
		DrawText("Seattle, WA", 610, 110, 30, A_BLUE_2);
		DrawText(weather.c_str(), 630, 155, 20, A_BLUE_1);
		DrawText(temperature.c_str(), 630, 185, 20, A_BLUE_1);
		
		std::string updateStr = "Updated " + std::to_string((int)(lastUpdateTime / 60) + 1) + " mins ago";
		DrawText(updateStr.c_str(), 630, 210, 10, A_GREEN_2);
	}
};

#endif
