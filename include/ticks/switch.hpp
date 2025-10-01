#ifndef INCLUDE_TICKS_SWITCH_TICK_HPP_
#define INCLUDE_TICKS_SWITCH_TICK_HPP_

#include "ticks/tick.hpp"
#include <chrono>

/*
 * SwitchTick: The tick that switches to the appropriate tick in the mission sequence.
 *
 * Its job is to switch to the appropriate tick in the mission sequence depending on the mission state.
 */
class SwitchTick : public Tick {
public:
    // Constructor that passes the shared state to the base Tick class.
    explicit SwitchTick(std::shared_ptr<MissionState> state);

    // Called once when this tick becomes the active state.
    void init() override;

    // Defines how often the `tick()` method is called.
    std::chrono::milliseconds getWait() const override;

    // The core logic that is executed repeatedly.
    Tick* tick() override;

private:
};

#endif // INCLUDE_TICKS_SWITCH_TICK_HPP_