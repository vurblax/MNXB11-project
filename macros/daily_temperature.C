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


void createTemperatureHistogram() {
    // Create a ROOT file to save the histogram
    TFile outputFile("temperature_histogram.root", "RECREATE");

    // Create a histogram to store temperature data
    TH1D* temperatureHistogram = new TH1D("temperature_histogram", "Temperature on August 23rd;Year;Temperature (°C)", (currentYear - 1722 + 1), 1722, currentYear + 1);

    // Loop through the years from 1722 to the present year or any desired endpoint
    for (int year = 1722; year <= currentYear; year++) {
        // For each year, obtain the temperature data for August 23rd
        double temperature = getTemperatureDataForYear(year);

        // Fill the histogram with the temperature for the current year
        temperatureHistogram->Fill(year, temperature);
    }

    // Set up the histogram properties (labels, colors, etc.) as needed

    // Save the histogram to the ROOT file
    temperatureHistogram->Write();

    // Calculate the mean and standard deviation of the histogram
    double mean = temperatureHistogram->GetMean();
    double stdev = temperatureHistogram->GetRMS();
    
    // Output the mean and standard deviation
    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Standard Deviation: " << stdev << std::endl;

    // Close the ROOT file
    outputFile.Close();
}

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











