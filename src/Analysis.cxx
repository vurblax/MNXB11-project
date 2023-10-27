#include <iostream>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "Analysis.h"
#include "WeatherData.h"
#include <map>

void CreateDecember25thHistogram(const std::string& output_tempdatafile) {
    TFile output_file{output_tempdatafile.c_str(), "UPDATE"};

    if (output_file.IsZombie()) {
        std::cerr << "Error: Could not open data file." << std::endl;
        return;
    }

    TTree* dataTree = dynamic_cast<TTree*>(output_file.Get("projectData"));
    if (!dataTree) {
        std::cerr << "Error: Could not find data tree in the file." << std::endl;
        return;
    }

    int year, month, day, hour;
    double airtemp;
    char quality;

    TBranch* yearBranch = dataTree->GetBranch("year");
    TBranch* monthBranch = dataTree->GetBranch("month");
    TBranch* dayBranch = dataTree->GetBranch("day");
    TBranch* hourBranch = dataTree->GetBranch("hour");
    TBranch* tempBranch = dataTree->GetBranch("airtemp");
    TBranch* qualityBranch = dataTree->GetBranch("quality");

    yearBranch->SetAddress(&year);
    monthBranch->SetAddress(&month);
    dayBranch->SetAddress(&day);
    hourBranch->SetAddress(&hour);
    tempBranch->SetAddress(&airtemp);
    qualityBranch->SetAddress(&quality);

    int minTemp = -10;
    int maxTemp = 30;

    std::map<double, int> temperatureData;

    Long64_t nEntries = dataTree->GetEntries();

    for (Long64_t entry = 0; entry < nEntries; ++entry) {
        dataTree->GetEntry(entry);
        // Add print statements to check values
        std::cout << "Year: " << year << " Month: " << month << " Day: " << day << " Hour: " << hour << " Temperature: " << airtemp << " Quality: " << quality << std::endl;
        // Check if the date is December 25th and if the temperature is within the specified range
        if (month == 12 && day == 25 && airtemp >= minTemp && airtemp <= maxTemp) {
            temperatureData[airtemp]++;
        }
    }
    // Create a histogram to display the temperature frequencies on December 25th
    TH1D* december25thHistogram = new TH1D("december25thHistogram", "Temperature Frequency on Dec 25th",
        static_cast<Int_t>(temperatureData.size()), minTemp - 0.5, maxTemp + 0.5);

    int index = 1;

    for (const auto& entry : temperatureData) {
        double airtemp = entry.first;
        int count = entry.second;
        december25thHistogram->SetBinContent(index, count);
        december25thHistogram->GetXaxis()->SetBinLabel(index, std::to_string(airtemp).c_str());
        index++;
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