//
// Created by Kenneth William on 2019-02-02.
//

#ifndef PANDAEXPRESS_OBEYSGRAVITY_H
#define PANDAEXPRESS_OBEYSGRAVITY_H

struct ObeysGravity {
    float gravityConstant;

    explicit ObeysGravity(float gravityConstant) :
            gravityConstant(gravityConstant) {}

    ObeysGravity() :
            gravityConstant(0.01f) {}
};

#endif //PANDAEXPRESS_OBEYSGRAVITY_H
