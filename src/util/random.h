//
// Created by Prayansh Srivastava on 2019-02-03.
//

#ifndef PANDAEXPRESS_RANDOM_H
#define PANDAEXPRESS_RANDOM_H

#include <random> // The header for the generators.
#include <limits>

class Random {
public:
    Random(unsigned int seed);

    void init(unsigned int seed);

    int nextInt(int from = std::numeric_limits<int>::min(),
                int to = std::numeric_limits<int>::max());

    float nextFloat(float from = std::numeric_limits<float>::min(),
                    float to = std::numeric_limits<float>::min());

private:
    std::mt19937 numberEngine; // Pseudo-random number engine (Mersenne Twister 19937 generator)
};


#endif //PANDAEXPRESS_RANDOM_H
