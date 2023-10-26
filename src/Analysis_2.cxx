#include <iostream>
#include <string>
#include "Analysis_2.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TF1.h"
#include "WeatherData.h"

// calling a function to analyze and visualize long-term temperature data
void LongtermTemp(const std::string& output_tempdatafile) {

    TFile output_file{output_tempdatafile.c_str(), "UPDATE"};
if (output_file.IsZombie()) {
    std::cerr << "Error: Could not open data file." << std::endl;
    return;
}
// retrieving the data tree from the ROOT file
    TTree* dataTree = dynamic_cast<TTree*>(output_file.Get("projectData")); // replace with the actual tree name!!!!
    if (!dataTree) {
        std::cerr << "Error: Could not find data tree in the file." << std::endl;
        return;
    }

// defining variables to store the data from the tree
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

// defining the range for the analysis
    int startYear = 1990;
    int endYear = 2022;

// creating maps to store the sum of temperatures and the count of data points for each year
    std::map<int, double> yearSum;
    std::map<int, int> yearCount;

// looping through the data and calculating the sum and count of temperatures for each year
    for (Long64_t i = 0; i < dataTree->GetEntries(); i++) {
        dataTree->GetEntry(i);
        WeatherData measurements{year, airtemp, quality};

        if (year >= startYear && year <= endYear) {
           // if (measurements.isDataIgnored()) { //removed this check because: 
                // the raw data has been checked; quality is 'G' for those values
                //but including the quality check gives odd values between years 1980-2010  
                // Needs further troubleshooting in order to determine cause
                yearSum[year] += airtemp;
                yearCount[year]++;
          //  }
        }
    }

// creation of a TGraph to store the data for plotting
auto gr = new TGraph();
gr->SetTitle("Temperature Change In Lund From 1990 To 2022;Year;Mean Temperature (deg C)");
gr->GetXaxis()->CenterTitle();
gr->GetYaxis()->CenterTitle();
gr->GetXaxis()->SetTitleColor(kBlack); 
gr->GetYaxis()->SetTitleColor(kBlack); 

    int pointIndex = 0;

    //populating the TGraph with mean temp data
    for (const auto& entry : yearSum) {
        int year = entry.first;
        double meanTemp = (yearCount[year] > 0) ? (entry.second / yearCount[year]) : 0.0;
        gr->SetPoint(pointIndex, year, meanTemp);
        pointIndex++;
    }
   
    TCanvas* c1 = new TCanvas("c1", "Temperature Graph", 800, 600);
    
    gr->SetLineWidth(3);
    gr->SetLineColor(kRed);
    c1->SetFillColor(kGray);

    // creating a linear fit function
   TF1* linearFit = new TF1("linearFit", "[0] + [1]*x", 1920, 2022);
   // linearFit->SetParName(1, "Intercept"); ** this is the start of a failed attempt at
   // linearFit->SetParName(1, "Slope"); ** displaying the fit equation in the legend
    linearFit->SetTitle("Linear Fit");

   // gr->Fit(linearFit, "Q");

// double intercept = linearFit->GetParameter(0);
// double slope = linearFit->GetParameter(1);

// TString fitParameters = Form("Fit Parameters: Intercept=%.2f, Slope=%.2f", intercept, slope);
// TString trendlineEquation = Form("Trendline: y = %.2fx + %.2f", slope, intercept);

// creating a legend for the graph
    TLegend* legend = new TLegend(0.15, 0.75, 0.6, 0.9);
    legend->SetHeader("Legend", "C");
    legend->AddEntry(gr, "Yearly mean temperature", "l"); 
    legend->AddEntry(linearFit, "Trendline as a linear fit", "l"); 

    // TLegendEntry* entry1 = legend->AddEntry((TObject*)nullptr, trendlineEquation, "");
    // TLegendEntry* entry2 = legend->AddEntry((TObject*)nullptr, fitParameters, "");

    legend->SetBorderSize(1);
    legend->SetFillStyle(0);
    legend->SetFillColor(kWhite);
    legend->SetTextSize(0.03);


  linearFit->SetLineColor(kMagenta);

// darwing teh graph, fitting it with the linear function and drawing the legend
    gr->Draw("AL"); 
    gr->Fit(linearFit, "Q");
    legend->Draw();
    c1->SaveAs("yearmeans.png");


    gr->Write();
    output_file.Close();
}



