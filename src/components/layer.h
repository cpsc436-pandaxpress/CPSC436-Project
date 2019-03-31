//
// Created by cowan on 21/03/19.
//

#ifndef PANDAEXPRESS_LAYER_H
#define PANDAEXPRESS_LAYER_H

const int TERRAIN_LAYER = 10;
const int ENEMY_LAYER = 15;
const int PROJECTILE_LAYER = 20;
const int ITEM_LAYER = 25;
const int PANDA_LAYER = 30;

class Layer {
public:
    int layer;

    Layer(int layer) {
        this->layer = layer;
    }
};

class CompareLayer {
public:
    CompareLayer() {};

    bool operator() (const Layer &left, const Layer &right) const {
        return left.layer < right.layer;
    }
};

#endif //PANDAEXPRESS_LAYER_H
