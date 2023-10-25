#include <TFile.h>
#include <TH1D.h>

// include C++ STL headers 
#include <string>

// ROOT library objects
#include "TCanvas.h" // canvas object
#include "TF1.h" // 1d function class
#include "TH1.h" // 1d histogram classes
#include "TLegend.h" // Labelling data
#include "TMath.h" // math functions
#include "DataExtraction.cxx" // Include the DataExtraction code (Needs to be modified according to new changes)


int main() {
    // Set the current year (replace with the actual current year)
    int currentYear = 2023; // Modify as needed

    // Call the function to create the temperature histogram
    createTemperatureHistogram();

    // Visualize the histogram
    TFile inputFile("temperature_histogram.root", "READ");
    TH1D* histogram = static_cast<TH1D*>(inputFile.Get("temperature_histogram"));
    TCanvas* canvas = new TCanvas("myCanvas", "Temperature Histogram", 800, 600);

    // Customize histogram appearance (if needed)
    histogram->SetFillColor(kRed + 1);
    histogram->Draw();

    return 0;
}










