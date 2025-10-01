#ifndef INCLUDE_TICKS_CVLOITER_TICK_HPP_
#define INCLUDE_TICKS_CVLOITER_TICK_HPP_

#include "ticks/tick.hpp"
#include <chrono>

/*
 * CVLoiterTick: The tick that waits on /capture.
 */
class CVLoiterTick : public Tick {
public:
    // Constructor that passes the shared state to the base Tick class.
    explicit CVLoiterTick(std::shared_ptr<MissionState> state);

    // Called once when this tick becomes the active state.
    void init() override;

    // Defines how often the `tick()` method is called.
    std::chrono::milliseconds getWait() const override;

    // The core logic that is executed repeatedly.
    Tick* tick() override;

private:
};

#endif // INCLUDE_TICKS_CVLOITER_TICK_HPP_