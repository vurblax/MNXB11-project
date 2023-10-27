
#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "TROOT.h"
#include "TCanvas.h"
#include "TH1D.h"
#include <TFile.h>
#include "TTree.h" 
#include "WeatherData.h"


void CreateDecember25thHistogram(const std::string& output_tempdatafile);


#endif