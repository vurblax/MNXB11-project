#include "DataExtraction.h"
#include <iostream>
#include <fstream>
#include <sstream>

DataExtractor::DataExtractor(const std::string& filePath) : csvFilePath(filePath) {
}

bool DataExtractor::ProcessCSVData() {
    //this opens the csv file I think
    std::ifstream inputFile(csvFilePath);
    if (!inputFile.is_open()) {
        std::cerr << "Couldn't open csv file, you need to close the file first" << std::endl;
        return false;
        // just an error message to make sure the file isn't open because it cant be read/changed in that case
    }


//the following snippet initilizes the variables that we want to store the data in (I think...)
std::string line;
std::string date, time, airtemp, quality;

//here we process the data in a while loop

while (std::getline(inputFile, line)) {
    //splits the line into four columns
    std::istringstream iss(line);
    if (iss >> date >> time >> airtemp >> quality) {
        //HERE is where we need to extract them into an output file of some sort!!!
        // NEW CODE FOR TFiles etc HERE
    }
}

inputFile.close();

return true;
}
