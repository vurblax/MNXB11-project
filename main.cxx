#include <iostream>
#include <string>
#include <chrono>
#include "DataExtraction.h"
#include "date.h"
#include "csv.h"


// first part where we extract the info from the csv file
int main() {
    // specify the dataset path to the cleaned file
    //this needs to be changed to specify each file we want to look at
    //right now it looks at Luleå
    const std::string csvFilePath = "./datasets/cleaned/smhi-opendata_1_162860_20231007_155220_Lulea.csv";
    const std::string outputFileName = "output.root";

    DataExtractor dataExtractor(csvFilePath, outputFileName);

    if (dataExtractor.ProcessCSVData(outputFileName)) {
        std::cout << "Data extraction completed successfully." << std::endl;
    } else {
        std::cerr << "Data extraction failed." << std::endl;
    }

    return 0;
}