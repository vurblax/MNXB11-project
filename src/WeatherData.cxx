#include "WeatherData.h"

WeatherData::WeatherData(int year, int month, int day, int hour, double temperature, char quality)
    : year{year}, month{month}, day{day}, hour{hour}, temperature{temperature}, quality{quality} { 
        
        if (std::isinf(temperature)) {
        throw std::invalid_argument("Infinite temperature value found!");
        
    }
}