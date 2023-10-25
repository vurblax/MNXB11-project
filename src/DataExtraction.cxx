#include "DataExtraction.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "date.h"
#include "csv.h"
#include "TFile.h"
#include "TTree.h"

DataExtractor::DataExtractor(const std::string& filePath, const std::string& outputFileName)
    : csvFilePath(filePath), outputFileName(outputFileName) {
}

bool DataExtractor::ProcessCSVData(const std::string& output_tempdatafile) {
    std::cout << "csvFilePath: " << csvFilePath << std::endl;
    std::ifstream inputFile(csvFilePath);
    if (!inputFile.is_open()) {
        std::cerr << "Couldn't open the CSV file." << std::endl;
        return false;
    }

    double_t airtemp;
    std::string quality;
    date::year_month_day date;
    std::string time_encoded;
    int hour(0);


    TFile output_file(output_tempdatafile.c_str(), "RECREATE");
    TTree tree("projectData", "Data for the project");
    if (!tree.GetDirectory()) {
        std::cerr << "Couldn't create the TTree." << std::endl;
        inputFile.close();
        output_file.Close();
        return false;
    }

    int year, month, day;

    
    tree.Branch("year", &year);
    tree.Branch("month", &month);
    tree.Branch("day", &day);
    tree.Branch("hour", &hour); 
    tree.Branch("airtemp", &airtemp);
    tree.Branch("quality", &quality);

    while (true) {
        std::string line;
        if (!std::getline(inputFile, line)) {
            break; 
        }

        std::istringstream iss(line);

//        if (iss >> year >> month >> day >> hour >> minute >> second >> airtemp >> quality || true) {
        if (iss >> year >> month >> day >> time_encoded >> airtemp >> quality || true) {
            date = date::year(year) / std::abs(month) / std::abs(day);

            size_t colon_pos = time_encoded.find(":");
            if (colon_pos != std::string::npos) {
                std::string hour_part = time_encoded.substr(0, colon_pos);
                hour = std::stoi(hour_part);
            }

            // Read out the first two letters in time_encoded 
            // time_encoded substring 
           // stoi 
            // transform to an int 
            // 

            tree.Fill();
        }
    }

inputFile.close();

if (tree.Write() < 0) {
    std::cerr << "Error writing TTree to output file." << std::endl;
    output_file.Close();
    return false;
}

tree.Write();
output_file.Close();

return true;
}