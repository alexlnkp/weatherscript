#include <iostream>

#include "jsonhandler.h"
#include "json.hpp"

#include "parser.h"

#ifdef IMPERIAL
	#define TEMP_SYMBOL "°F"
	#define TEMP_TYPE "temp_F"
	#define FEELSLIKE "FeelsLikeF"
	#define WINDSPEED "windspeedMiles"
	#define SPEEDSYMB "Mi/h"
#else
	#define TEMP_SYMBOL "°C"
	#define TEMP_TYPE "temp_C"
	#define FEELSLIKE "FeelsLikeC"
	#define WINDSPEED "windspeedKmph"
	#define SPEEDSYMB "M/s"
	#define CONVERT_WINDSPEED_TO_M_PER_S // If this variable is defined, wind speed is converted from km/h to m/s
#endif

#define WIND std::string("")
#define HUMIDITY std::string("")

int main(int argc, char **argv) {
	std::string res = (argc == 1) ? request("") : request(argv[1]);
	
	nlohmann::json json_res = nlohmann::json::parse(res);
	nlohmann::json json_out;

	std::string weather_code = json_res["current_condition"][0]["weatherCode"];
	std::string feels_like   = json_res["current_condition"][0][FEELSLIKE].get<std::string>();
	std::string humidity     = json_res["current_condition"][0]["humidity"].get<std::string>();
	std::string temp         = json_res["current_condition"][0][TEMP_TYPE].get<std::string>();
	int wind_speed = std::stoi(json_res["current_condition"][0][WINDSPEED].get<std::string>());

	std::string weather_symbol = get_weather_symbol(weather_code);

#ifdef CONVERT_WINDSPEED_TO_M_PER_S
	wind_speed /= 3.6;
#endif

	std::string tooltip;

	// Tooltip:

	// 󰖕 +5(-2)°C
	//  4 M/s
	//  74 %
	tooltip  = weather_symbol + ' ' + temp + '(' + feels_like + ')' +  + TEMP_SYMBOL +  '\n';
	tooltip += WIND + ' ' + std::to_string(wind_speed) + ' ' + SPEEDSYMB + '\n';
	tooltip += HUMIDITY + ' ' + humidity + ' ' + '%' + '\n';

	json_out["text"] = weather_symbol + ' ' + temp + TEMP_SYMBOL;
	json_out["tooltip"] = tooltip;

	std::cout << json_out << std::endl;
	
	return EXIT_SUCCESS;
}
