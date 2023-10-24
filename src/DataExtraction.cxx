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

    TFile output_file(output_tempdatafile.c_str(), "RECREATE");
    TTree tree("projectData", "Data for the project");

    date::year_month_day date;

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

    tree.Write();
    output_file.Close();

    return true;
}