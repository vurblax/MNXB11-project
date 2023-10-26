#include <iostream>
#include <string>
#include <chrono>
#include "DataExtraction.h"
#include "WeatherData.h"
#include "date.h"
#include "csv.h"
#include "Analysis.h"
#include "Analysis_2.h"
#include "Analysis_3.h"

int main() {
    // DATA EXTRACTION PART
    // ****note****: specify the dataset path to the cleaned file
    //this needs to be changed to specify each file we want to look at
    //right now it looks at Lund
    const std::string csvFilePath = "./datasets/cleaned/rawdata2_smhi-opendata_1_53430_20231007_155558_Lund.csv";
    const std::string outputFileName = "output.root";
    const std::string output_filename = "longterm_histogram.root";

    DataExtractor dataExtractor(csvFilePath, outputFileName);

    if (dataExtractor.ProcessCSVData(outputFileName)) {
        std::cout << "Data extraction completed successfully." << std::endl;
    } else {
        std::cerr << "Data extraction failed." << std::endl;
    }

// *******HERE STARTS Analysis*********

std::string output_tempdatafile2 = "output.root";
createTemperatureHistogram(output_tempdatafile);

// *******HERE STARTS Analysis_2*********

std::string output_tempdatafile = "output.root";
LongtermTemp(output_tempdatafile);



// *******HERE STARTS Analysis_3*********


std::vector<Measurement> measurements = load_measurements("your_data.csv"); // Replace with your data file

analyze_warmest_and_coldest_days(measurements, "output.root");

  return 0;
}
