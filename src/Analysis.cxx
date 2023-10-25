#include "Analysis.h"

// Function to get temperature data for December 25th in a given year
double getTemperatureDataForYear(int year) {
    // Implement your data retrieval logic here, based on your TTree
    // You need to extract and return the temperature data for December 25th in 'year'
    // You can use a TTree query or loop through your data as needed
    // Example: Replace this with your data extraction logic
    double temperature = 0.0; // Replace with actual data extraction
    return temperature;
}

void createTemperatureHistogram() {
    // Create a ROOT file to save the histogram
    TFile outputFile("temperature_histogram.root", "RECREATE");

    // Define the start and end years for your data
    int startYear = 1780;
    int endYear = 2022;

    // Create a histogram to store temperature data
    TH1D* temperatureHistogram = new TH1D("temperature_histogram", "Temperature on December 25th;Year;Temperature (°C)", (endYear - startYear + 1), startYear, endYear + 1);

    // Loop through the years and fill the histogram
    for (int year = startYear; year <= endYear; year++) {
        // For each year, obtain the temperature data for December 25th
        double temperature = getTemperatureDataForYear(year);

        // Fill the histogram with the temperature for December 25th in the current year
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