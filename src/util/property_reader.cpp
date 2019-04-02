#include <utility>

//
// Created by Prayansh Srivastava on 2019-04-01.
//

#include "property_reader.h"

std::string PropertyReader::get(std::string key) {
    return config_.at(key);
}

std::string PropertyReader::get(const char *key) {
    return get(std::string(key));
}

void PropertyReader::put(std::string key, std::string value) {
    config_[key] = value;
}

void PropertyReader::put(const char* key, std::string value) {
    put(std::string(key), std::string(value));
}

bool PropertyReader::load() {
    std::ifstream file(fileName_);

    config_.clear();
    std::string line;
    // Iterate through each line and split the content using delimeter
    if (!file.is_open()) {
        return false;
    }
    while (getline(file, line)) {
        auto delimPos = line.find('=');
        if (delimPos == -1) {
            return false;
        }
        std::string key = line.substr(0, delimPos);
        std::string value = line.substr(delimPos + 1);
        put(key, value);
    }
    // Close the File
    file.close();

    return true;
}

bool PropertyReader::save() {
    std::ofstream file(fileName_);
    if (!file.is_open()) {
        return false;
    }
    for (std::pair<std::string, std::string> element : config_) {
        file << element.first << "=" << element.second << std::endl;
    }
    file.close();
    return true;
}
