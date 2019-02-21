//
// Created by Prayansh Srivastava on 2019-02-11.
//
#include <iostream>
#include "csv_reader.h"

/* How to use
    CSVReader reader(filename);
    std::vector<std::vector<int>> dataList = reader.getData();
 */

std::vector<std::vector<int>> CSVReader::getData() {
    std::ifstream file(fileName);

    std::vector<std::vector<int>> dataList;

    std::string line = "";
    // Iterate through each line and split the content using delimeter
    while (getline(file, line)) {
        std::vector<int> vec;
        std::stringstream sStream(line);
        std::string tmp = "";
        char delim = ','; // define the delimiter to split by
        while (getline(sStream, tmp, delim)) {
            int i = 0;
            try {
                i = std::stoi(tmp);
            }
            catch (std::invalid_argument const &e) {
                std::cout << "Bad input: std::invalid_argument thrown:" << tmp << '\n';
            }
            catch (std::out_of_range const &e) {
                std::cout << "Integer overflow: std::out_of_range thrown:" << tmp << '\n';
            }
            vec.push_back(i);
        }
        dataList.push_back(vec);
    }
    // Close the File
    file.close();

    return dataList;
}
