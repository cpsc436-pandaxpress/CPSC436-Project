//
// Created by Kenneth William on 2019-03-28.
//

#include "Location.h"


void Location::addNeighbours(std::vector<std::vector<Location*>> grid){
    if(i<rows-1)
        neighbours.push_back(grid[i+1][j]);
    if(i>0)
        neighbours.push_back(grid[i-1][j]);
    if (j < cols -1)
        neighbours.push_back(grid[i][j+1]);
    if (j >0)
        neighbours.push_back(grid[i][j-1]);

}