//
// Created by cowan on 01/03/19.
//

#ifndef PANDAEXPRESS_TIMER_H
#define PANDAEXPRESS_TIMER_H

#include <unordered_map>

struct Watch {
    float time;
    float target_time;
};

class Timer {
public:
    bool is_done(std::string label);
    void add_timer(std::string label, float time);
    void update(float delta_time);

private:
    float currTime;
    std::unordered_map<std::string, Watch> watches;
};


#endif //PANDAEXPRESS_TIMER_H
