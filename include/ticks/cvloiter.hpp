#ifndef INCLUDE_TICKS_CVLOITER_TICK_HPP_
#define INCLUDE_TICKS_CVLOITER_TICK_HPP_

#include "ticks/tick.hpp"
#include "core/mission_state.hpp"
#include <chrono>

class CVLoiter : public Tick {
public:
    CVLoiter(std::shared_ptr<MissionState> state);

    void init();
    Tick* tick();

    std::chrono::milliseconds getWait() const;

private:
    std::shared_ptr<MissionState> state;
}

#endif