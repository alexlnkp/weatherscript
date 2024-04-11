
#ifndef JSONHANDLER_H

#include <string>
#include <map>

#define JSONHANDLER_H

#define CLOUDY "󰖐"
#define THUNDER_AND_RAIN "󰙾"
#define SUNNY "󰖙"
#define PARTLY_CLOUDY "󰖕"
#define RAINY "󰖗"
#define SNOWY "󰖒"

std::string get_weather_symbol(const std::string& weather_code);

const std::map<std::string, std::string> WEATHER_CODES = {
    {"200", THUNDER_AND_RAIN}, // Thunder with rain
    {"113", SUNNY}, // Sunny
    {"116", PARTLY_CLOUDY}, // Partly cloudy

    // Cloudy
    {"119", CLOUDY}, {"122", CLOUDY}, {"143", CLOUDY}, {"248", CLOUDY}, {"260", CLOUDY},

    // Rainy
    {"176", RAINY}, {"179", RAINY}, {"182", RAINY}, {"185", RAINY}, {"263", RAINY}, {"266", RAINY},
    {"281", RAINY}, {"284", RAINY}, {"293", RAINY}, {"296", RAINY}, {"299", RAINY}, {"302", RAINY},
    {"305", RAINY}, {"308", RAINY}, {"311", RAINY}, {"314", RAINY}, {"317", RAINY}, {"350", RAINY},
    {"353", RAINY}, {"356", RAINY}, {"359", RAINY}, {"362", RAINY}, {"365", RAINY}, {"368", RAINY},
    {"392", RAINY},
    
    // Snowy
    {"227", SNOWY}, {"230", SNOWY}, {"320", SNOWY}, {"323", SNOWY},
    {"326", SNOWY}, {"374", SNOWY}, {"377", SNOWY}, {"386", SNOWY},
    {"389", SNOWY},

    // Snowy?
    {"329", ""}, {"332", ""}, {"335", ""},
    {"338", ""}, {"371", ""}, {"395", ""}
};

#endif