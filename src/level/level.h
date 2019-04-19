//
// Created by cowan on 25/03/19.
//

#ifndef PANDAEXPRESS_LEVEL_H
#define PANDAEXPRESS_LEVEL_H

#include <vector>

typedef unsigned int LevelType;
const LevelType HORIZONTAL_LEVEL_TYPE = 0;
const LevelType VERTICAL_LEVEL_TYPE = 1;

class Level {
private:

    std::vector<std::vector<char>> rows_;
    size_t width_, height_;

public:
    static Level load_level(int id, LevelType type);
    static Level load_from_path(std::string file_name);
    Level();

    char get_tile_at(int x, int y) const;
    size_t width() const;
    size_t height() const;

};


#endif //PANDAEXPRESS_LEVEL_H
