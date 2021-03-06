#include "weatherGetter.h"

weatherGetter::weatherGetter(errorDisplay *errDisp)
{
	eDisp = errDisp;
	updateTime = 60 * 10;
	updateElapsed = 0;

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

	return ret;
}

void weatherGetter::update(float dt)
{
#if ON_RPI
	if (fut.valid())
	{
		try
		{
			std::future_status s = fut.wait_for(0ms);
			if (std::future_status::ready == s)
			{
				fut.get();

				eDisp->addErrString("recieved new weather data");
			}
		}
		catch (const std::future_error &e)
		{
			std::cerr << "future error: " << e.code() << std::endl;
			eDisp->addErrString("future error");
		}
	}
#endif

	updateElapsed += dt;
	if (updateElapsed >= updateTime)
	{
		updateElapsed = 0;
		updateViaThread();
	}
}

void weatherGetter::updateViaThread()
{
	eDisp->addErrString("sending speedtest async update");

#if ON_RPI
	fut = std::async(std::launch::async, [this] {
		this->getWeather();
	});
#endif
}

void weatherGetter::draw()
{
	DrawText("Seattle, WA", 605, 15, 30, A_BLUE_2);
	DrawText(weather.c_str(), 615, 50, 20, A_BLUE_1);
	DrawText(temperature.c_str(), 615, 80, 20, A_BLUE_1);

	// std::string updateStr = "Updated " + std::to_string((int)(lastUpdateTime / 60) + 1) + " mins ago";
	// DrawText(updateStr.c_str(), 615, 105, 10, A_GREEN_2);
}
