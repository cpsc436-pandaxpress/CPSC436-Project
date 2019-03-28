//
// Created by Kenneth William on 2019-03-27.
//

#include "a_star_system.h"
#include <iostream>
#include "util/Location.h"

int cols=0;
int rows=0;



float distance(Location* a, Location* b){
    //calculate distance then return it
    return abs(a->i-b->i)+abs(a->j-b->j);
}

bool contains(std::vector<Location*> list, Location* location){
    for(int i = 0; i<list.size(); i++){
        if(list[i]==location){
            return true;
        }
    }
    return false;
}


AStarSystem::AStarSystem() {}

void AStarSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    // construct a view for all entities with a sprite
    int level = 0;
    std::vector<Location*> openSet;
    std::vector<Location*> closedSet;
    std::vector<Location*> path;
    Location* start;
    Location* end;

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
    std::vector<std::vector<Location*>> grid;

    for(int i = 0; i<rows; i++){
        std::vector<Location*> row;
        for(int j=0; j<cols; j++){
            row.push_back(new Location(i,j));
            if(dataList[i][j]=='1'){
                row[row.size()-1]->obstacle=true;
            }

        }
        grid.push_back(row);

    }

    // Add neighbours
    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {
            grid[i][j]->addNeighbours(grid);
            std::cout << grid[i][j]->obstacle;
        }
        std::cout << "\n";
    }
    start = grid[1][15];
    start->obstacle=false;
    end = grid[8][15];
    end->obstacle=false;
    openSet.push_back(start);


    while(openSet.size() > 0){
        int winner = 0;
        for(int i = 0; i<openSet.size(); i++){
                if(openSet[i]->f < openSet[winner]->f){
                    winner = i;
                }
        }
        Location* current = openSet[winner];
        if(current == end){
            //Done
            Location* temp = current;
            while(temp != NULL){
                path.insert(path.begin(), temp);
                temp=temp->previous;
            }
            break;
        }
        openSet.erase(openSet.begin()+winner);
        closedSet.push_back(current);

        std::vector<Location*> neighbours = current->neighbours;
        for(int i=0; i<neighbours.size(); i++){
            Location* neighbour = neighbours[i];
            if(!contains(closedSet, neighbour) && !neighbour->obstacle){
                float tempG = current->g +1.;

                if(contains(openSet, neighbour)){
                    if(tempG < neighbour->g){
                        neighbour->g = tempG;
                    }
                }else{
                    neighbour->g = tempG;
                    openSet.push_back(neighbour);
                }

                neighbour->h = distance(neighbour, end);
                neighbour->f = neighbour->g+neighbour->h;
                neighbour->previous = current;
            }

        }

    }

    int u=0; // Only here to have breakpoint
}