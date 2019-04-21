//
// Created by cowan on 21/03/19.
//

#ifndef PANDAEXPRESS_LAYER_H
#define PANDAEXPRESS_LAYER_H

const int BACKGROUND_LAYER = 0;
const int DEFAULT_LAYER = 10;
const int TERRAIN_LAYER = 20;
const int ENEMY_LAYER = 25;
const int PROJECTILE_LAYER = 30;
const int ITEM_LAYER = 35;
const int TEXT_LAYER = 40;
const int BOSS_LAYER = 43;
const int PANDA_LAYER = 60;
const int OVERLAY_LAYER = 100;
const int MENU_LAYER = 105;

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
