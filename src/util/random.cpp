//
// Created by Prayansh Srivastava on 2019-02-03.
//

#include "random.h"

Random::Random(unsigned int seed) {
    init(seed);
}

void Random::init(unsigned int seed) {
    numberEngine.seed(seed);
}

int Random::nextInt(int from, int to) {
    std::uniform_int_distribution<int> unii(from, to);
    return unii(numberEngine);
}

float Random::nextFloat(float from, float to) {
    std::uniform_real_distribution<float> unif(from, to);
    return unif(numberEngine);
}

