//
// Created by cowan on 01/03/19.
//

#include "timer.h"

using namespace std;

Timer::Timer() {
    curr_time = 0;
}

void Timer::save_watch(string label, float time) {
    watches[label] = {time, curr_time + time};
}

bool Timer::is_done(std::string label) {
    if (watches.find(label) == watches.end()) {
        return false;
    }

    return watches[label].target_time <= curr_time;
}

void Timer::update(float delta_time) {
    curr_time = curr_time + delta_time;
}

void Timer::reset_watch(std::string label) {
    if (watches.find(label) == watches.end()) {
        return;
    }

    Watch watch = watches[label];
    watch.target_time = curr_time + watch.time;
    watches[label] = watch;
}

bool Timer::exists(string label) {
    return (watches.find(label) != watches.end());
}

void Timer::remove(std::string label) {
    watches.erase(label);
}