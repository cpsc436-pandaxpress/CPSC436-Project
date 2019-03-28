//
// Created by Kenneth William on 2019-03-28.
//

#ifndef PANDAEXPRESS_LOCATION_H
#define PANDAEXPRESS_LOCATION_H

#include <stdio.h>
#include <vector>

class Location {

public:
    int i =0;
    int j = 0;
    float f = 0.;
    float g = 0.;
    float h = 0.;
    Location* previous = NULL;
    bool obstacle=false;
    std::vector<Location*> neighbours;
    Location(){};
    Location(int i, int j){
        this->i = i;
        this->j = j;
    }

    void addNeighbours(std::vector<std::vector<Location*>> grid);

private:
    // Hardcoded size of boss room.  Can change this if we decide to use it somewhere else;
    int cols = 16;
    int rows = 9;
};


#endif //PANDAEXPRESS_LOCATION_H
