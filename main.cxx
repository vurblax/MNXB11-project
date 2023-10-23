#include <iostream>
#include "DataExtraction.h"

// first part where we extract the info from the csv file
int main() {
    // Specify the dataset path
    const std::string csvFilePath = "./datasets/smhi-opendata_1_162860_20231007_155220_Lulea.csv";

    CSVProcessor csvProcessor(csvFilePath);

    csvProcessor.ProcessCSVData();


// here we need a second part to get the output in a file we can use, like a TFile and a TTree thing

    return 0;
}