#ifndef INCLUDE_TICKS_SWITCH_TICK_HPP_
#define INCLUDE_TICKS_SWITCH_TICK_HPP_

#include "ticks/tick.hpp"
#include <chrono>

/*
 * EndTIck: The tick that ends the mission.
 */
class EndTick : public Tick {
public:
    // Constructor that passes the shared state to the base Tick class.
    explicit EndTick(std::shared_ptr<MissionState> state);

    // Called once when this tick becomes the active state.
    void init() override;

    // The core logic that is executed repeatedly.
    Tick* tick() override;

private:
};

#endif // INCLUDE_TICKS_END_TICK_HPP_