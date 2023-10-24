#include "DataExtraction.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "TFile.h"
#include "TTree.h"
#include "date.h"
#include "csv.h"

DataExtractor::DataExtractor(const std::string& filePath, const std::string& outputFileName)
 : csvFilePath(filePath), outputFileName(outputFileName) {
}

bool DataExtractor::ProcessCSVData(const std::string& output_tempdatafile) {
    //this opens the csv file I think
    std::ifstream inputFile(csvFilePath);
    if (!inputFile.is_open()) {
        std::cerr << "Couldn't open csv file, you need to close the file first" << std::endl;
        return false;
        // just an error message to make sure the file isn't open because it cant be read/changed in that case
    }

//the following snippet initilizes the variables that we want to store the data in (I think...)
std::string line;        
double airtemp;
std::string quality;

TFile output_file(output_tempdatafile.c_str(), "RECREATE");
TTree tree("projectData", "Data for the project");

date::year_month_day date;   
date::hh_mm_ss time; 
date::year_month_day* date_ptr = nullptr;
date::hh_mm_ss* time_ptr = nullptr;

tree.Branch("date", &date);
tree.Branch("time", &time);
tree.Branch("airtemp",&airtemp);
tree.Branch("quality", &quality);

//here we process the data in a while loop

while (std::getline(inputFile, line)) {
    //splits the line into the four columns/variables
    std::istringstream iss(line);
    std::string date_str;
    std::string time_str;

    if (iss >> date_str >> time_str >> airtemp >> quality) {
        // Now, date_str and time_str have been read successfully, and you can use them.
        date = date::from_stream(date_str);
        time = date::from_stream(time_str);

        // Extract year, month, and day components from the date
        int year = static_cast<int>(date.year());
        unsigned month = static_cast<unsigned>(date.month());
        unsigned day = static_cast<unsigned>(date.day());
      
        date_ptr = &date;
        time_ptr = &time;

        tree.Fill();
    }
}


inputFile.close();

tree.Write();
output_file.Close();

return true;
}
