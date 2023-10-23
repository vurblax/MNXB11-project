#ifndef DATAEXTRACTION_H
#define DATAEXTRACTION_H

#include <string>
#include "csv.h"

class DataExtractor {
public:
    DataExtractor(const std::string& filePath);
    bool ProcessCSVData();

private:
    std::string csvFilePath;
};

#endif 