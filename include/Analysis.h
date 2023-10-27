
#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "TROOT.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TTree.h" // Add this include for working with TTrees

void CreateDecember25thHistogram(const std::string& output_tempdatafile2);

class Analysis {
public:
    Analysis();
    void SetupROOT();
    void CreateCanvas();
    void DrawHistogram(TH1D* histogram);

    
};

#endif