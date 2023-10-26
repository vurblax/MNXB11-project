#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <string>
#include <vector>
#include <iostream>

#include <TFile.h>
#include <TH1D.h>
#include <TTree.h>

#include "WeatherData.h"


void createTemperatureHistogram(const std::string& output_tempdatafile2);


#endif /* ANALYSIS_H */