//
// Created by Prayansh Srivastava on 2019-02-11.
//

#ifndef PANDAEXPRESS_CSV_READER_H
#define PANDAEXPRESS_CSV_READER_H

#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>

/*
 * A class to read data from a csv file.
 */
class CSVReader {
private:
    std::string fileName;
    std::string delimeter;

public:
    CSVReader(std::string filename, std::string delm = ",") :
            fileName(filename), delimeter(delm) {}

    // Function to fetch data from a CSV File
    std::vector<std::vector<char>> getData();
};


#endif //PANDAEXPRESS_CSV_READER_H
