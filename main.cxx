#include <iostream>
#include "DataExtraction.h"


// first part where we extract the info from the csv file
int main() {
    // specify the dataset path to the cleaned file
    //this needs to be changed to specify each file we want to look at
    //right now it looks at Luleå
    const std::string csvFilePath = "./datasets/cleaned/smhi-opendata_1_162860_20231007_155220_Lulea.csv";
    const std::string outputFileName = "ouput.root";

    DataExtractor dataExtractor(csvFilePath, outputFileName);

    //a nice little message here
    if (dataExtractor.ProcessCSVData()) {
        std::cout << "Data extraction completed successfully." << std::endl;
    } else {
        std::cerr << "Data extraction failed." << std::endl;
    }


// here we need a second part to get the output in a file we can use, like a TFile and a TTree thing

    return 0;
}