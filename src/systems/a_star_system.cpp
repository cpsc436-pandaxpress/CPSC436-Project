//
// Created by Kenneth William on 2019-03-27.
//

#include "a_star_system.h"
#include <iostream>

int cols=0;
int rows=0;

class Location{

public:
    int i;
    int j;
    float f=0.;
    float h=0.;
    bool obstacle=false;
    std::vector<Location*> neighbours;
    Location(){};
    Location(int i, int j){
        this->i = i;
        this->j = j;
    }

    void addNeighbours(std::vector<std::vector<Location>> grid){
        int x = i;
        int y = j;
        if(i<cols-1)
            this->neighbours.push_back(&grid[i+1][j]);
        if(i>0)
            this->neighbours.push_back(&grid[i-1][j]);
        if (j < rows -1)
            this->neighbours.push_back(&grid[i][j+1]);
        if (j >0)
            this->neighbours.push_back(&grid[i][j-1]);

    }

};

AStarSystem::AStarSystem() {}

void AStarSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    // construct a view for all entities with a sprite
    int level = 0;

    std::string level_path = levels_path("");
    std::string levelFile = level_path + "boss_level_" + std::to_string(level) + ".csv";
    CSVReader reader(levelFile);
    std::vector<std::vector<char>> dataList = reader.getData();
    for (int i = 0; i < dataList[0].size(); i++) {
        std::vector<char> col;
        col.reserve(9);
        for (int j = 0; j < 9; j++) {
            col.push_back(dataList[j][i]);
        }

    }
    cols = dataList[0].size();
    rows =9;

    std::vector<std::vector<Location>> grid;
    for(int i = 0; i<rows; i++){
        std::vector<Location> row;
        for(int j=0; j<cols; j++){
            row.push_back(Location(i,j));
            if(dataList[i][j]=='1'){
                row[row.size()-1].obstacle=true;
            }

        }
        grid.push_back(row);

    }



    for (int j = 0; j < rows; j++) {

        for (int i = 0; i < cols; i++) {
            grid[j][i].addNeighbours(grid);
            std::cout << grid[j][i].obstacle;
        }
        std::cout << "\n";
    }


    int x=0;
}