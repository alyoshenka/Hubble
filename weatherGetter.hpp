#ifndef WEATHERGETTER_HPP
#define WEATHERGETTER_HPP
#pragma once

#include "pyHelper.hpp"
#include <iostream>

class weatherGetter
{
	CppPyObject pModule;
    CppPyInstance* pyInstance;

public:

	weatherGetter()
	{
        pyInstance = new CppPyInstance();

		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.path.append('/home/jay/WeatherPi')");

		CppPyObject pName = PyUnicode_FromString("weather");
		pModule = PyImport_Import(pName);

		if (!pModule) { PyErr_Print(); }
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
std::cout << 1 << std::endl;
			if (pValue)
			{
				ret = _PyUnicode_AsString(pValue);
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
			}
			else { PyErr_Print(); }
		}
		else { PyErr_Print(); }

		return ret;
	}
};

#endif
