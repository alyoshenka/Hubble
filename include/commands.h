#pragma once

// defines cl commands to query sensor data

// test
#define basic_cmd "basic command"

// particle photon
#define particle_temp "/home/jay/get_temp.sh"
#define particle_humd "/home/jay/get_humd.sh"

// speedtest
#define get_up_speed "speedtest | grep Upload"
#define get_dn_speed "speedtest | grep Download"

// weather
#define get_weather "weatherpi weather"
#define get_temperature "weatherpi temperature"

#define get_weather_full "/home/jay/WeatherPi/main.py weather"
#define get_temperature_full "/home/jay/WeatherPi/main.py temperature"

// CPU temp
#define get_cpu_temp "measure_temp"
#define get_cpu_temp_full "/opt/vc/bin/vcgencmd measure_temp"
