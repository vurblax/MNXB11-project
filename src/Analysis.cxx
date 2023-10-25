
#include "Analysis.h"

/*Temperature in December 25th in Lund*/

void createTemperatureHistogram() {
    // Create a ROOT file to save the histogram
    TFile outputFile("temperature_histogram.root", "RECREATE");

    // Create a histogram to store temperature data
    TH1D* temperatureHistogram = new TH1D("temperature_histogram", "Temperature on August 23rd;Year;Temperature (°C)", (currentYear - 1780 + 1), 1780, currentYear + 1);

    // Loop through the years from 1722 to the present year or any desired endpoint
    for (int year = 1780; year <= currentYear; year++) {
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
