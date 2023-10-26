#ifndef WEATHERDATA_H
#define WEATHERDATA_H
#include <cmath>
#include <stdexcept>

class WeatherData {
 public:
 
  WeatherData(int year, int month, int day, int hour, double temperature, char quality);
  
  bool isDataIgnored() const {
        return ignoreData;
    }

 private:
  int year; 
  int month;
  int day; 
  int hour; 
  double temperature; 
  char quality;
  bool ignoreData = false; // Initialized to false by default
};

//Constructor implementation
WeatherData::WeatherData(int year, int month, int day, int hour, int minute, int second, double temperature, char quality)
    : year(year), month(month), day(day), hour(hour), temperature(temperature), quality(quality) {
}

#endif /* WEATHERDATA_H */