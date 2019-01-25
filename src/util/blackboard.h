//
// Created by alex on 20/01/19.
//

#pragma once

#include "input_manager.h"


// Struct containing all our singletons
// All require individual initialization
struct Blackboard {
    InputManager input_manager;
};