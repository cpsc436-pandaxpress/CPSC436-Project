//
// Created by cowan on 01/03/19.
//

#ifndef PANDAEXPRESS_TIMER_H
#define PANDAEXPRESS_TIMER_H

#include <unordered_map>
#include <string>

enum WatchStatus {
    RUNNING, DONE, NOT_FOUND
};

struct Watch {
    float time;
    float target_time;
    WatchStatus status;
};

class Timer {
public:
    Timer();
    bool is_done(std::string label);
    void save_watch(std::string label, float time);
    void update(float delta_time);
    void reset_watch(std::string label);
    WatchStatus status(std::string label);
    void remove(std::string label);

private:
    float curr_time;
    std::unordered_map<std::string, Watch> watches;
};


#endif //PANDAEXPRESS_TIMER_H
