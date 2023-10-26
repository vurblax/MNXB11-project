#include <iostream>
#include <string>
#include "Analysis_2.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"

LongtermTemp::LongtermTemp(const char* extractedData) : rootFile(extractedData, "READ") {
    //initializing the class!!
    longtermTree = (TTree*)rootFile.Get("longtermTree");
    annualMeanTemps.resize(100, 0.0);
}

void LongtermTemp::CalculateAnnualMeans(TH1D* yearMeanHist) {
    Double_t airtemp;
    longtermTree->SetBranchAddress("airtemp", &airtemp);

Long64_t nEntries = longtermTree->GetEntries();
Long64_t yearsInData =nEntries / (3 * 365);
Long64_t startEntry = (yearsInData > 100) ? (nEntries - 100 * 3 * 365) : 0;

int year= 0;
double dailySum = 0.0;
int measurementsPerYear = 3 * 365;

for (Long64_t i = startEntry; i < nEntries; i++) {
    longtermTree->GetEntry(i);
    dailySum += airtemp;


    if ((i + 1) % measurementsPerYear == 0) {
        annualMeanTemps[year] = dailySum / measurementsPerYear;
        dailySum = 0.0;
        year++;
        }
    }
    for (int i = 0; i < 100; i++) {
        yearMeanHist->Fill(i, annualMeanTemps[i]);
    }
}

void PlotLongtermHistogram(const std::vector<double>& annualMeanTemps) {

    TCanvas* c1 = new TCanvas("c1", "Annual Mean Temperatures", 800, 600);

    TH1D* hist = new TH1D("hist", "Annual Mean Temperatures", 100, 0, 100);

    for (int i = 0; i < 100; i++) {
        hist->Fill(i, annualMeanTemps[i]);
    }

    hist->SetXTitle("Year");
    hist->SetYTitle("Mean Temperature");

    hist->Draw();

    c1->SaveAs("longterm_histogram.png");
}



