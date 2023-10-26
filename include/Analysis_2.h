#ifndef ANALYSIS_2_H
#define ANALYSIS_2_H

#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <iostream>
#include <string>
#include <vector>

class LongtermTemp {
public:
    LongtermTemp(const char* extractedData);
    void CalculateAnnualMeans(TH1D* yearMeanHist);
    std::vector<double> annualMeanTemps;
    
private:
    TFile rootFile;
    TTree* longtermTree;

};

void PlotLongtermHistogram(const std::vector<double>& annualMeanTemps);

#endif 