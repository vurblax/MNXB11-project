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
    std::string date_str;
    std::string time;

    date::year_month_day date;

    TFile output_file(output_tempdatafile.c_str(), "RECREATE");
    TTree tree("projectData", "Data for the project");
    if (!tree.GetDirectory()) {
        std::cerr << "Couldn't create the TTree." << std::endl;
        inputFile.close();
        output_file.Close();
        return false;
    }

    tree.Branch("date", &date);
    tree.Branch("time", &time);
    tree.Branch("airtemp", &airtemp);
    tree.Branch("quality", &quality);

    while (true) {
        std::string line;
        if (!std::getline(inputFile, line)) {
            break; // End of file
        }

        std::istringstream iss(line);

        if (iss >> date_str >> time >> airtemp >> quality) {
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