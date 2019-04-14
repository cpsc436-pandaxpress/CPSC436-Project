//
// Created by Kenneth William on 2019-03-27.
//

#include "a_star_system.h"


int cols=0;
int rows=0;
std::vector<std::vector<location*>> grid;



float manhattanDistance(location *a, location *b){
    return abs(a->i - b->i)+abs(a->j - b->j);
}

bool contains(std::vector<location*> list, location* location){
    for(int i = 0; i<list.size(); i++){
        if(list[i]==location){
            return true;
        }
    }
    return false;
}


AStarSystem::AStarSystem(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    createGrid(blackboard, registry);
}



void AStarSystem::createGrid(Blackboard &blackboard, entt::DefaultRegistry &registry) {
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

    for(int i = 0; i<rows; i++){
        std::vector<location*> row;
        for(int j=0; j<cols; j++){
            row.push_back(new location(i,j));
            if(dataList[i][j]=='1' || dataList[i][j]=='b'){
                row[row.size()-1]->platform=true;
            }

        }
        grid.push_back(row);

    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j]->addNeighbours(grid);
        }
    }

}

location* AStarSystem::getGridLocation(float x, float y){
    int i = (x+800-X_OFFSET)/100;
    int j = (y+450-Y_OFFSET)/100;

    return grid[j][i];
}

Coordinates* AStarSystem::getScreenLocation(int j, int i){
    float x = (i*100)-800;
    float y = (j*100)-450+Y_OFFSET;

    Coordinates* c = new Coordinates(x,y);
    return c;
}

std::vector<Coordinates*> AStarSystem::getProjectilePath(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    location* start;
    location* end;
    std::vector<location*> path;
    std::vector<Coordinates*> coordinatePath;

    auto dracula = registry.view<Dracula, Transform>();

    for (auto entity: dracula) {

        auto& transform = dracula.get<Transform>(entity);
        start = getGridLocation(transform.x, transform.y);
    }

    auto panda = registry.view<Panda, Transform>();

    for (auto entity: panda) {

        auto& transform = panda.get<Transform>(entity);
        end = getGridLocation(transform.x, transform.y);
    }

    path = findPath(start, end);

    for(int i=0; i<path.size(); i++){
        Coordinates* temp = getScreenLocation(path[i]->i,path[i]->j);
        coordinatePath.push_back(temp);
    }

    return coordinatePath;

}

/***
 * A* Pathfinding algorithm adapted from https://www.youtube.com/watch?v=aKYlikFAV4k
 * and Wikipedia pseudocode https://en.wikipedia.org/wiki/A*_search_algorithm
 */
std::vector<location*> AStarSystem::findPath(location* start, location* end){
    std::vector<location*> openSet;
    std::vector<location*> closedSet;
    std::vector<location*> path;
    openSet.push_back(start);

    while(!openSet.empty()){
        int best = 0;
        for(int i = 0; i<openSet.size(); i++){
            if(openSet[i]->f_score < openSet[best]->f_score && !openSet[best]->platform){
                best = i;
            }
        }
        location* current = openSet[best];
        if(current == end){
            location* temp = current;
            while(temp != NULL){
                path.insert(path.begin(), temp);
                temp=temp->previous;
            }
            //Reset Grid
            for(int i = 0; i<rows; i++) {
                for (int j = 0; j < cols; j++) {
                    grid[i][j]->previous=NULL;
                    grid[i][j]->f_score=0;
                    grid[i][j]->g_score=0;
                    grid[i][j]->h_score=0;
                    openSet.clear();
                    closedSet.clear();
                }
            }
            return path;
        }
        openSet.erase(openSet.begin()+best);
        closedSet.push_back(current);

        std::vector<location*> neighbours = current->neighbours;
        for(int i=0; i<neighbours.size(); i++){
            location* neighbour = neighbours[i];
            if(!contains(closedSet, neighbour) && !neighbour->platform){
                float tempG = current->g_score +1.f;

                if(contains(openSet, neighbour)){
                    if(tempG < neighbour->g_score){
                        neighbour->g_score = tempG;
                    }
                }else{
                    neighbour->g_score = tempG;
                    openSet.push_back(neighbour);
                }

                neighbour->h_score = manhattanDistance(neighbour, end);
                neighbour->f_score = neighbour->g_score+neighbour->h_score;
                neighbour->previous = current;
            }

        }

    }

return path;
}


void AStarSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {

}