#ifndef INCLUDE_CVLOITER_HPP_
#define INCLUDE_CVLOITER_HPP_

#include "core/mission_state.hpp"
#include "ticks/tick.hpp"
#include "camera/mock.hpp"
#include <chrono>

class CVLoiterTick : public Tick {
public:
    explicit CVLoiterTick(std::shared_ptr<MissionState> state);
    void init() override;
    Tick* tick() override; 
    std::chrono::milliseconds getWait() const override;
private:
    // TBA
};

#endif