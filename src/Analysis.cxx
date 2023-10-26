#include <iostream>
#include <string>
#include "Analysis.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TTree.h"

void CreateDecember25thHistogram(const std::string& output_tempdatafile2) {
    TFile output_file{output_tempdatafile2.c_str(), "UPDATE"};

    if (output_file.IsZombie()) {
        std::cerr << "Error: Could not open data file." << std::endl;
        return;
    }

    TTree* dataTree = dynamic_cast<TTree*>(output_file.Get("projectData")); // Replace with the actual tree name
    if (!dataTree) {
        std::cerr << "Error: Could not find data tree in the file." << std::endl;
        return;
    }

    int year;
    double airtemp;
    char quality;

    TBranch* yearBranch = dataTree->GetBranch("year");
    TBranch* tempBranch = dataTree->GetBranch("airtemp");
    TBranch* qualityBranch = dataTree->GetBranch("quality");

    yearBranch->SetAddress(&year);
    tempBranch->SetAddress(&airtemp);
    qualityBranch->SetAddress(&quality);

    int startYear = 1920;
    int endYear = 2022;
    int desiredMonth = 12; // December
    int desiredDay = 25;   // 25th

    TH1D* december25thMeanHist{new TH1D{"december25thMeanHist", "Mean Temperature on Dec 25th",
        endYear - startYear + 1, startYear - 0.5, endYear + 0.5}};

    Long64_t nEntries = dataTree->GetEntries();
    for (Long64_t entry = 0; entry < nEntries; ++entry) {
        dataTree->GetEntry(entry);
        if (year >= startYear && year <= endYear) {
            // Check if the date is December 25th and the data quality is good
            if (quality == 'G' && airtemp != -9999 &&
                static_cast<int>(airtemp) == desiredDay &&
                static_cast<int>(airtemp / 100) == desiredMonth) {
                december25thMeanHist->Fill(year, airtemp);
            }
        }
    }

    december25thMeanHist->SetXTitle("Year");
    december25thMeanHist->SetYTitle("Mean Temperature");

    december25thMeanHist->Write();
    output_file.Close();
}