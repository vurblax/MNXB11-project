#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <vector>
#include <string>
#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"

struct Measurement {
  int year;
  double temperature;
};

std::vector<Measurement> load_measurements(const std::string& data_file);
void analyze_warmest_and_coldest_days(const std::vector<Measurement>& measurements, const std::string& output_filename);

#endif

