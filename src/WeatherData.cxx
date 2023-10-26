#include "WeatherData.h"

WeatherData::WeatherData(int year, int month, int day, int hour, double temperature, char quality)
    : year{year}, month{month}, day{day}, hour{hour}, temperature{temperature}, quality{quality} { 
        
        if (std::isinf(temperature)) {
        throw std::invalid_argument("Infinite temperature value found!");
        
    }
       // Check if the quality is 'Y' (bad data) or 'G' (good data)
    if (quality == 'Y' || quality == 'G') {
        if (std::isinf(temperature)) {
            throw std::invalid_argument("Infinite temperature value found!");
        }
    } else {
        // If quality is not 'Y' or 'G', set a flag to ignore this data
        ignoreData = true;
    }
}