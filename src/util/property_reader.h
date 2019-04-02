#include <utility>

//
// Created by Prayansh Srivastava on 2019-04-01.
//

#ifndef PANDAEXPRESS_PROPERTY_READER_H
#define PANDAEXPRESS_PROPERTY_READER_H

#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_map>

class PropertyReader {
private:
    std::string fileName_;
    std::unordered_map<std::string, std::string> config_;

public:
    PropertyReader(std::string filename) :
            fileName_(std::move(filename)), config_() {}

    PropertyReader(const char *filename) :
            fileName_(std::string(filename)), config_() {}

    // Function to fetch data from a CSV File
    std::string get(std::string key);
    std::string get(const char* key);

    void put(std::string key, std::string value);
    void put(const char* key, std::string value);

    bool load();

    bool save();
};


#endif //PANDAEXPRESS_PROPERTY_READER_H
