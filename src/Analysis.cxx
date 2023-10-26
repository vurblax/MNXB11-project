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

    double airtemp;
    TBranch* tempBranch = dataTree->GetBranch("airtemp");
    tempBranch->SetAddress(&airtemp);

    int minTemp = -20; // Define your desired temperature range
    int maxTemp = 30;

    // Define the number of bins based on the temperature range
    int nBins = maxTemp - minTemp + 1;

    TH1D* december25thHistogram{new TH1D{"december25thHistogram", "Temperature on Dec 25th Histogram",
        nBins, minTemp - 0.5, maxTemp + 0.5}};

    Long64_t nEntries = dataTree->GetEntries();
    for (Long64_t entry = 0; entry < nEntries; ++entry) {
        dataTree->GetEntry(entry);
        // Check if the date is December 25th and the temperature is within the specified range
        if (static_cast<int>(airtemp) == 25 && airtemp >= minTemp && airtemp <= maxTemp) {
            december25thHistogram->Fill(airtemp);
        }
    }

    december25thHistogram->SetXTitle("Temperature on December 25th");
    december25thHistogram->SetYTitle("Entries");

    december25thHistogram->Write();
    output_file.Close();
}