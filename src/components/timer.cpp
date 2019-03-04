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
    for (auto &it: watches) {
        if (it.second.target_time <= curr_time) {
            it.second.status = DONE;
        }
    }
}

void Timer::reset_watch(std::string label) {
    if (watches.find(label) == watches.end()) {
        return;
    }

    Watch watch = watches[label];
    watch.target_time = curr_time + watch.time;
    watch.status = RUNNING;
    watches[label] = watch;
}

WatchStatus Timer::status(std::string label) {
    if (watches.find(label) == watches.end()) {
        return NOT_FOUND;
    }
    return watches[label].status;
}

void Timer::remove(std::string label) {
    watches.erase(label);
}