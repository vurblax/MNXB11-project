#include <iostream>
#include <string>
#include <cmath> 
#include <map>
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "Analysis.h"
#include "WeatherData.h"


void CreateDecember25thHistogram(const std::string& output_tempdatafile) {
    // Open the ROOT file for updating (from the raw data we got before)
    TFile output_file{output_tempdatafile.c_str(), "UPDATE"};
    // Checks if the file containing the data opened succesfully, it not it displays an error
    if (output_file.IsZombie()) {
        std::cerr << "Error: Could not open data file." << std::endl;
        return;
    }
    // Access the data tree from the ROOT file and retrivieng data
    TTree* dataTree = dynamic_cast<TTree*>(output_file.Get("projectData"));
    if (!dataTree) {
        std::cerr << "Error: Could not find data tree in the file." << std::endl;
        return;
    }
    
    // Defining variables to store the data from the tree
    int year, month, day, hour;
    double airtemp;
    char quality;

    // Access the data tree from the ROOT file
    TBranch* yearBranch = dataTree->GetBranch("year");
    TBranch* monthBranch = dataTree->GetBranch("month");
    TBranch* dayBranch = dataTree->GetBranch("day");
    TBranch* hourBranch = dataTree->GetBranch("hour");
    TBranch* tempBranch = dataTree->GetBranch("airtemp");
    TBranch* qualityBranch = dataTree->GetBranch("quality");
    
    // Set the addresses for the TBranches to read data into variables
    yearBranch->SetAddress(&year);
    monthBranch->SetAddress(&month);
    dayBranch->SetAddress(&day);
    hourBranch->SetAddress(&hour);
    tempBranch->SetAddress(&airtemp);
    qualityBranch->SetAddress(&quality);

    // Defining minimum and maximum temperature for the analysis
    int minTemp = -20;
    int maxTemp = 30;
    
    // Create a map to store temperature data and their frequencies
    std::map<double, int> temperatureData;
    
    // Get the total number of entries (data points) and loop through each entry in the TTree
    Long64_t nEntries = dataTree->GetEntries();

    for (Long64_t entry = 0; entry < nEntries; ++entry) {
        dataTree->GetEntry(entry);
        // Print the data 
        std::cout << "Year: " << year << " Month: " << month << " Day: " << day << " Hour: " << hour << " Temperature: " << airtemp << " Quality: " << quality << std::endl;
        // Round temperature values 
        double roundedTemperature = std::round(airtemp);
        // Check if the date is December 25th and if the temperature within the range
        if (month == 12 && day == 25 && roundedTemperature >= minTemp && roundedTemperature <= maxTemp) {
            temperatureData[roundedTemperature]++;
        }
    }
    // Create a histogram to display the temperature frequencies on December 25th
    TH1D* december25thHistogram = new TH1D("december25thHistogram", "Temperature Frequency on December 25th",
        static_cast<Int_t>(temperatureData.size()), minTemp - 0.5, maxTemp + 0.5);

    int index = 1;
    // Populate the histogram with temperature frequencies
    for (const auto& entry : temperatureData) {
        double airtemp = entry.first;
        int count = entry.second;
        december25thHistogram->SetBinContent(index, count);
        december25thHistogram->GetXaxis()->SetBinLabel(index, std::to_string(airtemp).c_str());
        index++;
    }
    
    // Set axis labels and create a canvas for displaying the histogram
    december25thHistogram->SetXTitle("Temperature on December 25th [°C]");
    december25thHistogram->SetYTitle("Frequency");
    december25thHistogram->GetXaxis()->CenterTitle();
    december25thHistogram->GetYaxis()->CenterTitle();

    TCanvas* c1 = new TCanvas("c1", "December 25th Temperature Histogram", 800, 600);
    c1->SetFillColor(kGray);

    // Makes a pretty, beautiful histogram
    december25thHistogram->SetLineColor(kMagenta);
    december25thHistogram->SetLineWidth(3);
    december25thHistogram->SetFillColor(kCyan);

    // Draw histogram and saves it as png for report 
    december25thHistogram->Draw("HIST");
    c1->SaveAs("december25th_histogram.png");

    december25thHistogram->Write();
    output_file.Close();
}
