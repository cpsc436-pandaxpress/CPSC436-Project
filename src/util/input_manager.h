//
// Created by alex on 20/01/19.
//

#pragma once

class InputManager {
private:
    bool should_exit_;
public:
    InputManager();

    // update
    void update();

    // returns true if an exit event has been polled
    bool should_exit();

    //TODO: implement input handling methods
};