#include <iostream>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "WeatherData.h"

void CreateDecember25thHistogram(const std::string& output_tempdatafile2) {
    TFile output_file{output_tempdatafile2.c_str(), "UPDATE"};

    if (output_file.IsZombie()) {
        std::cerr << "Error: Could not open data file." << std::endl;
        return;
    }

    TTree* dataTree = dynamic_cast<TTree*>(output_file.Get("projectData"));
    if (!dataTree) {
        std::cerr << "Error: Could not find data tree in the file." << std::endl;
        return;
    }

    double airtemp;
    TBranch* tempBranch = dataTree->GetBranch("airtemp");
    tempBranch->SetAddress(&airtemp);

    int minTemp = -10; // Define your desired temperature range
    int maxTemp = 30;

    // Define the number of bins based on the temperature range
    int nBins = maxTemp - minTemp + 1;

    // Create a histogram to count the occurrences of each temperature
    TH1D* december25thHistogram{new TH1D{"december25thHistogram", "Temperature on Dec 25th",
        nBins, minTemp - 0.5, maxTemp + 0.5}};

    Long64_t nEntries = dataTree->GetEntries();

    for (Long64_t entry = 0; entry < nEntries; ++entry) {
        dataTree->GetEntry(entry);
        // Check if the date is December 25th
        int month = static_cast<int>(airtemp / 10000);
        int day = static_cast<int>(airtemp / 100) % 100;
        if (month == 12 && day == 25 && airtemp >= minTemp && airtemp <= maxTemp) {
            december25thHistogram->Fill(airtemp);
        }
    }

    december25thHistogram->SetXTitle("Temperature on December 25th");
    december25thHistogram->SetYTitle("Frequency");

    TCanvas* c1 = new TCanvas("c1", "December 25th Temperature Histogram", 800, 600);
    c1->SetFillColor(kGray);

    december25thHistogram->SetLineColor(kRed);
    december25thHistogram->SetLineWidth(3);

    // Draw with HIST option to create a proper histogram
    december25thHistogram->Draw("HIST");
    c1->SaveAs("december25th_histogram.png");

    december25thHistogram->Write();
    output_file.Close();
}


