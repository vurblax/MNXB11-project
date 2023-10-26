#include "WeatherData.h"

WeatherData::WeatherData(int year, int month, int day, int hour, double airtemp, char quality)
    : year{year}, month{month}, day{day}, hour{hour}, airtemp{airtemp}, quality{quality} { 
    // Checks if temperature has an infinite value, if so, skip
        if (std::isinf(airtemp)) {
        throw std::invalid_argument("Infinite temperature value found!");
        
    }
    
    // Initialize the flag to true, assuming data is ignored by default
    ignoreData = true;
    
    // Check if the quality is 'G' (good)
    if (quality == 'G') {
        // Set the flag to not ignore this data
        ignoreData = false;
    }
}