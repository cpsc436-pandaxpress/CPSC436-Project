//
// Created by cowan on 25/03/19.
//

#include <cstdio>
#include <string>
#include <util/constants.h>
#include <util/csv_reader.h>
#include "level.h"

Level::Level() : width_(0), height_(0), rows_(nullptr) {}

Level::~Level() {
    for (int i = 0; i < height_; i++) {
        delete[] rows_[i];
    }
    delete[] rows_;
}

char Level::get_tile_at(int x, int y) const {
    return rows_[y][x];
}

Level Level::load_level(int id, LevelType type) {
    switch (type) {
        case HORIZONTAL_TYPE: {
            std::string level_path = levels_path("");
            std::string level_file = level_path + "level_" + std::to_string(id) + ".csv";
            return load_from_path(level_file);
        }

        case VERTICAL_TYPE: {
            std::string level_path = levels_path("");
            std::string level_file = level_path + "vlevel_" + std::to_string(id) + ".csv";
            return load_from_path(level_file);
        }

        default: {
            throw "Invalid LevelType given";
        }
    }
}

Level Level::load_from_path(std::string path) {
    CSVReader reader(path);
    auto data = reader.getData();

    Level level;
    level.rows_ = new char*[data.size()];
    level.height_ = (int) data.size();

    int x = 0, y = 0;
    for (const auto &row : data) {
        level.rows_[x] = new char[row.size()];
        if (level.width_ < (int) row.size())
            level.width_ = (int) row.size();

        for (const char tile : row) {
            level.rows_[y][x] = tile;
            x++;
        }
        y++;
    }

    return level;
}

size_t Level::width() const {
    return width_;
}

size_t Level::height() const {
    return height_;
}
