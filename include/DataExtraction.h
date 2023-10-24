#ifndef DATAEXTRACTION_H
#define DATAEXTRACTION_H

#include <string>
#include "csv.h"
#include "date.h"

class DataExtractor {
public:
    DataExtractor(const std::string& filePath, const std::string& outputFileName);
    bool ProcessCSVData(const std::string& output_tempdatafile);

private:
    std::string csvFilePath;
    std::string outputFileName;
};

#endif 