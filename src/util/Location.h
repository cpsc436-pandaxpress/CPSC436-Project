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
    float f_score = 0.;
    float g_score = 0.;
    float h_score = 0.;
    Location* previous = NULL;
    bool platform = false;
    std::vector<Location*> neighbours;
    Location(){};
    Location(int i, int j){
        this->i = i;
        this->j = j;
    }

    void addNeighbours(std::vector<std::vector<Location*>> grid);

private:
    // Hardcoded size of boss room.  Can change this if we decide to use it somewhere else;
    int cols = 34;
    int rows = 18;
};


#endif //PANDAEXPRESS_LOCATION_H
