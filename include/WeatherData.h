#ifndef WEATHERDATA_H
#define WEATHERDATA_H
#include <cmath>
#include <stdexcept>

class WeatherData {
 public:
  // Note: Bad idea, using two adjacent parameters that can be switched
  // accidentally!
  WeatherData(int year, int month, int day, int hour, int minute, int second, double temperature, int quality);

 private:
  int year; 
  int month;
  int day; 
  int hour; 
  int minute; 
  int second; 
  double temperature; 
  int quality;
};
