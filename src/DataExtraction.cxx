#include "DataExtraction.h"
#include <iostream>

CSVProcessor::CSVProcessor(const std::string& filePath) : reader(filePath) {
    reader.read_header(io::ignore_no_column, "Datum", "Tid (UTC)", "Lufttemperatur");
}

CSVProcessor::~CSVProcessor() {
    // Destructor
}

void CSVProcessor::ProcessCSVData() {
    while (reader.read_row(datum, tid, lufttemperatur)) {
        std::replace(datum.begin(), datum.end(), ';', ' ');
        std::replace(tid.begin(), tid.end(), ';', ' ');
        std::replace(lufttemperatur.begin(), lufttemperatur.end(), ';', ' ');

        std::cout << "Datum: " << datum << std::endl;
        std::cout << "Tid (UTC): " << tid << std::endl;
        std::cout << "Lufttemperatur: " << lufttemperatur << std::endl;
    }
}