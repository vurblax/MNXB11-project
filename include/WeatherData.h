#ifndef WEATHERDATA_H
#define WEATHERDATA_H
#include <cmath>
#include <stdexcept>

class WeatherData {
 public:
 
  WeatherData(int year, int month, int day, int hour, int minute, int second, double temperature, char quality);

 private:
  int year; 
  int month;
  int day; 
  int hour; 
  int minute; 
  int second; 
  double temperature; 
  char quality;
};

//Constructor implementation
WeatherData::WeatherData(int year, int month, int day, int hour, int minute, int second, double temperature, char quality)
    : year(year), month(month), day(day), hour(hour), minute(minute), second(second), temperature(temperature), quality(quality) {
}

#endif /* WEATHERDATA_H */