#include <iostream>
#include <string>
#include <chrono>
#include "DataExtraction.h"
#include "date.h"
#include "csv.h"
#include "Analysis_2.h"

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

// *******HERE STARTS Analysis_2*********
const char* extractedData = "output.root"; 
 //                    here ^^^^^^
 // is where we need to make changes if we change
 // the name or path of our output root file that was
 // created in the data extraction

std::string longterm_histogram = "output.root";
LongtermTemp(extractedData, longterm_histogram);



// more analyses to be added here
return 0;
}