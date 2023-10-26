#include "Analysis.h"

void createTemperatureHistogram(const std::string& output_tempdatafile2) {
    // Define the start and end years for your data
    int startYear = 1780;
    int endYear = 2022;

    // Create a ROOT file to save the histogram
    TFile outputFile("temperature_histogram.root", "RECREATE");

    // Create a histogram to store temperature data
    TH1D* temperatureHistogram = new TH1D("temperature_histogram", "Temperature on December 25th;Year;Temperature (°C)", (endYear - startYear + 1), startYear, endYear + 1);

    for (int year = startYear; year <= endYear; year++) {
        // For each year, obtain a collection of temperature data for the entire year
        std::vector<WeatherData> yearTemperatureData = getTemperatureDataForYear(year);

        // Iterate over the data points for the year and fill the histogram
        for (const WeatherData& dataPoint : yearTemperatureData) {
            // Fill the histogram with the temperature data for the current year and data point
            temperatureHistogram->Fill(year, dataPoint.getTemperature());
        }
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
