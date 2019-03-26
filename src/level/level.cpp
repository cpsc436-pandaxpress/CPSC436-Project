//
// Created by cowan on 25/03/19.
//

#include <cstdio>
#include <string>
#include <util/constants.h>
#include <util/csv_reader.h>
#include "level.h"

Level::Level() : width_(0), height_(0), rows_() {}

char Level::get_tile_at(int x, int y) const {
    if (y >= rows_.size())
        return '\0';

    if (x >= rows_[y].size())
        return '\0';

    return rows_[y][x];
}

Level Level::load_level(int id, LevelType type) {
    switch (type) {
        case HORIZONTAL_LEVEL_TYPE: {
            std::string level_path = levels_path("");
            std::string level_file = level_path + "level_" + std::to_string(id) + ".csv";
            return load_from_path(level_file);
        }

        case VERTICAL_LEVEL_TYPE: {
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
    level.height_ = data.size();

    int y = 0;
    for (const auto &row : data) {
        level.rows_.push_back(row);
        if (level.width_ < row.size())
            level.width_ = row.size();

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
