#ifndef DATAEXTRACTION_H
#define DATAEXTRACTION_H

#include <string>
#include "csv.h"

class CSVProcessor {
public:
    CSVProcessor(const std::string& filePath);
    ~CSVProcessor();
    void ProcessCSVData();

private:
    io::CSVReader<4, io::trim_chars<' '>, io::no_quote_escape<';'>> reader;
    std::string datum, tid, lufttemperatur;
};

#endif 