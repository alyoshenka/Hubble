
#ifndef DHT22QUERY_HPP
#define DHT22QUERY_HPP
#pragma once

class dht22Query
{
	const std::string command = "particle call Medusa ";
	const std::string temp = "temp";
	const std::string humd = "humd";
	
	int get(std::string cmd) 
	{
		system(cmd.c_str());
		std::string line;
		getline(std::cin, line);
		try
		{
			int ret = std::stoi(line);
			return ret;
		}
		catch(std::invalid_argument const &e) { return -8; }
		return -9;
	}
	
public:
	int getTemp() { return get(command + temp); }		
	int getHumd() { return get(command + humd); }
};

#endif
