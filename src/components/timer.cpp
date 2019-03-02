//
// Created by cowan on 01/03/19.
//

#include "timer.h"

using namespace std;

void Timer::add_timer(string label, float time) {
    watches[label] = {time, currTime + time};
}

bool Timer::is_done(std::string label) {
    if (watches.find(label) == watches.end())
    {
        return false;
    }

    return watches[label].target_time <= currTime;
}

void Timer::update(float delta_time) {
    currTime += delta_time;
}