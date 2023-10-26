#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <string>
#include <vector>
#include <iostream>

#include <TFile.h>
#include <TH1D.h>
#include <TTree.h>

#include "WeatherData.h"


// Function to get temperature data for December 25th in a given year
double getTemperatureDataForYear(const std::vector<WeatherData>& WeatherData, const std::string& TempYearHist);

void createTemperatureHistogram();


#endif /* ANALYSIS_H */