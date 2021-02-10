#include "sensor.h"

<<<<<<< HEAD:sensor.cpp

int dht22Query::get(std::string file) 
=======
int dht22Query::get(std::string file)
>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c:src/sensor.cpp
{
#if ON_RPI
	std::fstream outFile;
	outFile.open("/home/jay/Hubble/" + file + ".txt");
	if (!outFile)
	{
		return -8;
	}

	std::string line;
	getline(outFile, line);
	
	std::cout << "read: " << line << std::endl;
	eDisp->addErrString("read: " + line);
	try
	{
		int ret = std::stoi(line);
		return ret;
	}
	catch (...)
	{
		return -9;
	}
	return -10;
#endif
	return -11;
}

void dht22Query::queryThread() { system("/home/jay/Hubble/query.sh"); }

dht22Query::dht22Query()
{
#if ON_RPI
	pyInstance = new CppPyInstance();

	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('/home/jay/Hubble')");

	CppPyObject pName = PyUnicode_FromString("runSensor");
	pModule = PyImport_Import(pName);
	if (!pModule)
	{
		PyErr_Print();
	}

	if (nullptr == pModule)
	{
		PyErr_Print();
	}

	CppPyObject pFunc = PyObject_GetAttrString(pModule, "go");
	if (pFunc && PyCallable_Check(pFunc))
	{
		CppPyObject pValue = PyObject_CallObject(pFunc, NULL);
		if (pValue)
		{
			std::cout << "thing: ";
			std::string ret = _PyUnicode_AsString(pValue);
			std::cout << ret << std::endl;
			
			// if(nullptr != eDisp) { eDisp->addErrString("thing: " + ret);}
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
#endif
}

<<<<<<< HEAD:sensor.cpp
dht22Query::~dht22Query() { 
	pyInstance = nullptr; 
	eDisp = nullptr;
=======
dht22Query::~dht22Query()
{
#if ON_RPI
	pyInstance = nullptr;
#endif
>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c:src/sensor.cpp
}

void dht22Query::queryData()
{
#if ON_RPI
	query = std::thread(queryThread);
	query.detach();
#else
	queryThread();
#endif
}

int dht22Query::getTemp() { return get(temp); }
int dht22Query::getHumd() { return get(humd); }

<<<<<<< HEAD:sensor.cpp

sensorDisplay::sensorDisplay(errorDisplay* errDisp)
=======
sensorDisplay::sensorDisplay()
>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c:src/sensor.cpp
{
	eDisp = errDisp;
	sensor.eDisp = errDisp;	
	
	temp = humd = 99;

	sensorUpdateTime = 60 * 10;
	displayUpdateTime = sensorUpdateTime + 30;
	updateElapsedTime = sensorUpdateTime;
	lastUpdateTime = 0;

	shouldQuery = true;
}

sensorDisplay::~sensorDisplay() {}

void sensorDisplay::update(float frameTime)
{
	updateElapsedTime += frameTime;
	lastUpdateTime += frameTime;
	if (updateElapsedTime > displayUpdateTime)
	{
		std::cout << "update" << std::endl;
		eDisp->addErrString("update sensor display");
		
		updateElapsedTime = 0;
		shouldQuery = true;
		int tTemp = sensor.getTemp();
		int tHumd = sensor.getHumd();
		if (tTemp > 0)
		{
			temp = tTemp;
		}
		if (tHumd > 0)
		{
			humd = tHumd;
		}
		if (tTemp > 0 && tHumd > 0)
		{
			lastUpdateTime = 0;
		}
	}
<<<<<<< HEAD:sensor.cpp
	else if(updateElapsedTime > sensorUpdateTime && shouldQuery && ON_RPI)
=======
	else if (updateElapsedTime > sensorUpdateTime && shouldQuery && !ON_RPI)
>>>>>>> 7a245092389d4584eb22bd111eea983d92eac42c:src/sensor.cpp
	{
		std::cout << "query" << std::endl;
		eDisp->addErrString("query sensor");
		
		sensor.queryData();
		shouldQuery = false;
	}
}

void sensorDisplay::draw()
{
	DrawText("Photon", 610, 115, 30, A_BLUE_2);

	std::string tStr = /*std::to_string(temp) + */ "°f";
	std::string hStr = /*std::to_string(humd) + */ "%";
	DrawText(tStr.c_str(), 620, 150, 25, A_BLUE_1);
	DrawText(hStr.c_str(), 690, 150, 25, A_BLUE_1);
	// DrawRectangleRec(Rectangle{ 590, 15, 25, 25 }, A_PURPLE_2);

	std::string updateStr = "Updated ";
	int mins = lastUpdateTime / 60 + 1;
	// updateStr += std::to_string(mins) + " mins ago";
	updateStr = "x mins ago";

	// DrawText(updateStr.c_str(), 500, 45, 10, A_GREEN_2);
}
