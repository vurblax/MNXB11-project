#include "WeatherData.h"

WeatherData::WeatherData(int year, int month, int day, int hour, int minute, int second, double temperature, int quality)
    : year{year}, month{month}, day{day}, hour{hour}, minute{minute}, second{second}, temperature{temperature}, quality{quality} { 
        
        if (std::isinf(signal) || std::isinf(background)) {
    throw std::invalid_argument("Infinite measurement found!");
  }
  // Check that neither signal nor background is NaN (not a number)
  if (std::isnan(signal) || std::isnan(background)) {
    throw std::invalid_argument("Infinite measurement found!");
  }
  // Let's say that a valid measurement can't have a negative id, signal, or
  // background (use what suits your actual data!)
  if (id < 0) {
    throw std::invalid_argument(
        "A measurement cannot have a negative ID but was " +
        std::to_string(id));
  }
  if (signal < 0 || background < 0) {
    throw std::invalid_argument(
        "A signal or background value cannot be negative, but got signal " +
        std::to_string(signal) + " and background " +
        std::to_string(background));
  };
}