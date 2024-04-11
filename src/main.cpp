#include <iostream>
#include <stdio.h>

#include "jsonhandler.h"
#include "json.hpp"

#include "parser.h"



#ifdef IMPERIAL
  #define TEMP_SYMBOL "°F"
  #define TEMP_TYPE "temp_F"
#else
  #define TEMP_SYMBOL "°C"
  #define TEMP_TYPE "temp_C"
#endif



int main(int argc, char **argv) {

    std::string res = (argc == 1) ? request("") : request(argv[1]);
    
	nlohmann::json json_res = nlohmann::json::parse(res);

    std::string weather_code = json_res["current_condition"][0]["weatherCode"];
    std::string weather_symbol = get_weather_symbol(weather_code);
	std::string temp = json_res["current_condition"][0][TEMP_TYPE].get<std::string>();
	
	std::cout << weather_symbol << ' ' << temp << TEMP_SYMBOL << std::endl;
    
	return EXIT_SUCCESS;
}
