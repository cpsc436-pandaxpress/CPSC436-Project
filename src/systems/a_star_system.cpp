//
// Created by Kenneth William on 2019-03-27.
//

#include "a_star_system.h"


int cols=0;
int rows=0;
std::vector<std::vector<Location*>> grid;
bool initialized = false;



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

}

Location* AStarSystem::getGridLocation(float x, float y){
    int i = (x+800)/100;
    int j = (y+450)/100;

    int u=0; // Only here to have breakpoint
    std::cout<<"gridlocation " << i << " " << j << "\n";
    return grid[j][i];
}

Coordinates* AStarSystem::getScreenLocation(int j, int i){
    float x = (i*100)-800;
    float y = (j*100)-450;

    int u=0; // Only here to have breakpoint

    Coordinates* c = new Coordinates(x,y);
    return c;
}

std::vector<Coordinates*> AStarSystem::getProjectilePath(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    Location* start;
    Location* end;
    //createGrid(blackboard, registry);
    std::vector<Location*> path;
    std::vector<Coordinates*> coordinatePath;

    auto jacko = registry.view<Jacko, Transform>();

    for (auto entity: jacko) {

        auto& transform = jacko.get<Transform>(entity);
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

std::vector<Location*> AStarSystem::findPath(Location* start, Location* end){
    std::vector<Location*> openSet;
    std::vector<Location*> closedSet;
    std::vector<Location*> path;

    start->obstacle=false;

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
            //Reset Grid
            for(int i = 0; i<rows; i++) {
                for (int j = 0; j < cols; j++) {
                    //grid[i][j]->neighbours.clear();
                    grid[i][j]->previous=NULL;
                    grid[i][j]->f=0;
                    grid[i][j]->g=0;
                    grid[i][j]->h=0;
                    openSet.clear();
                    closedSet.clear();
                }
            }
            return path;
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


}

void AStarSystem::update(Blackboard &blackboard, entt::DefaultRegistry &registry) {
    // construct a view for all entities with a sprite
    /*
    Location* start;
    Location* end;

    start = grid[1][15];
    end = grid[8][15];

    std::vector<Location*> path;
    path = getProjectilePath(blackboard, registry);
    //path = findPath(start, end);
    int u=0; // Only here to have breakpoint
    */
}