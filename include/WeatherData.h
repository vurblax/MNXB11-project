#ifndef WEATHERDATA_H
#define WEATHERDATA_H
#include <cmath>
#include <stdexcept>

class WeatherData {
 public:
 
  WeatherData(int year, int month, int day, int hour, double airtemp, char quality);
  WeatherData(int year, double airtemp, char quality);
  bool isDataIgnored() const {
        return ignoreData;
    }

 private:
  int year; 
  int month;
  int day; 
  int hour; 
  double airtemp; 
  char quality;
  bool ignoreData = false; // Initialized to false by default

};


#endif /* WEATHERDATA_H */