//
// Created by Prayansh Srivastava on 2019-02-11.
//
#include <iostream>
#include "csv_reader.h"

/* How to use
    CSVReader reader(filename);
    std::vector<std::vector<int>> dataList = reader.getData();
 */

std::vector<std::vector<char>> CSVReader::getData() {
    std::ifstream file(fileName);

    std::vector<std::vector<char>> dataList;

    std::string line = "";
    // Iterate through each line and split the content using delimeter
    while (getline(file, line)) {
        std::vector<char> vec;
        std::stringstream sStream(line);
        std::string tmp = "";
        char delim = ','; // define the delimiter to split by
        while (getline(sStream, tmp, delim)) {
            char c = '\0';
            if (tmp.length() > 0) {
                c = tmp[0];
            } else {
                std::cout << "Bad input: no chars given\n";
            }
            vec.push_back(c);
        }
        dataList.push_back(vec);
    }
    // Close the File
    file.close();

    return dataList;
}
