#include <iostream>
#include <string>
#include "Analysis_2.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"

void LongtermTemp(const std::string& output_tempdatafile) {
                    //const char* probably needs to change
                    //i want that line to retrieve our extracted data
                    //that is, from output.root
    TFile output_file{output_tempdatafile.c_str(), "UPDATE"};
if (output_file.IsZombie()) {
    std::cerr << "Error: Could not open data file." << std::endl;
    return;
}

    TTree* dataTree = dynamic_cast<TTree*>(output_file.Get("projectData")); // replace with the actual tree name!!!!
    if (!dataTree) {
        std::cerr << "Error: Could not find data tree in the file." << std::endl;
        return;
    }

    std::vector<double> annualMeanTemps;
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

    TH1D* yearMeanHist{new TH1D{"yearMeanHist", "Annual Mean Temperatures", 
        endYear - startYear + 1, startYear - 0.5, endYear + 0.5}};

    Long64_t nEntries = dataTree->GetEntries();
    for (Long64_t entry = 0; entry < nEntries; ++entry) {
        dataTree->GetEntry(entry);
        WeatherData measurements{year, airtemp, quality};
        if (year >= startYear && year <= endYear) {
            if (measurements.isDataIgnored()) 
              yearMeanHist->Fill(year, airtemp);
        }
    }

    yearMeanHist->SetXTitle("Year");
    yearMeanHist->SetYTitle("Mean Temperature");

    yearMeanHist->Write();
    output_file.Close();
}



