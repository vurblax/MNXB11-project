#include "DataExtraction.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "date.h"
#include "csv.h"
#include "TFile.h"
#include "TTree.h"

// declaring the data extractor class
DataExtractor::DataExtractor(const std::string& filePath, const std::string& outputFileName)
    : csvFilePath(filePath), outputFileName(outputFileName) {
}

// calling the function
bool DataExtractor::ProcessCSVData(const std::string& output_tempdatafile) {

// just a message to clarify which file is being used
    std::cout << "csvFilePath: " << csvFilePath << std::endl;

// opening the csv file
    std::ifstream inputFile(csvFilePath);

// error check
    if (!inputFile.is_open()) {
        std::cerr << "Couldn't open the CSV file." << std::endl;
        return false;
    }

// declaring the variables which we use to store our variables from the csv
    double_t airtemp;
    std::string quality;
    date::year_month_day date;
    std::string time_encoded;
    int hour(0);
    int year, month, day;

// creating the TFile and TTree where the data is then stored
    TFile output_file(output_tempdatafile.c_str(), "RECREATE");
    TTree tree("projectData", "Data for the project");
    if (!tree.GetDirectory()) {
// error check
        std::cerr << "Couldn't create the TTree." << std::endl;
        inputFile.close();
        output_file.Close();
        return false;
    }
    
// defining the branches
    tree.Branch("year", &year);
    tree.Branch("month", &month);
    tree.Branch("day", &day);
    tree.Branch("hour", &hour); 
    tree.Branch("airtemp", &airtemp);
    tree.Branch("quality", &quality);

// here the data from the csv file (line by line) is being read and stored into the tree
    while (true) {
        std::string line;
        if (!std::getline(inputFile, line)) {
            break; 
        }

// here is where the data from each line are being turned into variables for the output
        std::istringstream iss(line);
        if (iss >> year >> month >> day >> time_encoded >> airtemp >> quality || true) {
// the date variable here gets 'divided' into its separate values
            date = date::year(year) / std::abs(month) / std::abs(day);

// here we extract just the hour from the time 
// which in the csv is using the format hh:mm:ss
// the hour then gets turned into an int bc we need it as a number
            size_t colon_pos = time_encoded.find(":");
            if (colon_pos != std::string::npos) {
                std::string hour_part = time_encoded.substr(0, colon_pos);
                hour = std::stoi(hour_part);
            }

            tree.Fill();
        }
    }

inputFile.close();

// error check
if (tree.Write() < 0) {
    std::cerr << "Error writing TTree to output file." << std::endl;
    output_file.Close();
    return false;
}

tree.Write();
output_file.Close();

return true;
}