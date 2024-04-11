#include "jsonhandler.h"
#include "json.hpp"

std::string get_weather_symbol(const std::string& weather_code) {
    auto it = WEATHER_CODES.find(weather_code);
    return it != WEATHER_CODES.end() ? it->second : "?";
}