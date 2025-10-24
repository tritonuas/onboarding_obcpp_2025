#ifndef INCLUDE_TICKS_CVLOITER_TICK_HPP_
#define INCLUDE_TICKS_CVLOITER_TICK_HPP_

#include "ticks/tick.hpp"
#include "ticks/switch.hpp"
#include <chrono>

class CvLoiterTick : public Tick {
public:
    explicit CvLoiterTick(std::shared_ptr<MissionState> state);

    void init() override;

    Tick* tick() override;

    std::chrono::milliseconds getWait() const override;
};

#endif