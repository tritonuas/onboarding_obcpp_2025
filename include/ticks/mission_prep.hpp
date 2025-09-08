#ifndef INCLUDE_TICKS_MISSION_PREP_TICK_HPP_
#define INCLUDE_TICKS_MISSION_PREP_TICK_HPP_

#include "ticks/tick.hpp"
#include <chrono>

/*
 * MissionPrepTick: The first tick in the mission sequence.
 *
 * Its job is to simulate a preparation phase, like running system checks.
 * It waits for a fixed duration before transitioning to the next state.
 */
class MissionPrepTick : public Tick {
public:
    // Constructor that passes the shared state to the base Tick class.
    explicit MissionPrepTick(std::shared_ptr<MissionState> state);

    // Called once when this tick becomes the active state.
    void init() override;

    // Defines how often the `tick()` method is called.
    std::chrono::milliseconds getWait() const override;

    // The core logic that is executed repeatedly.
    Tick* tick() override;

private:
    // A timestamp to keep track of when this tick started its work.
    std::chrono::time_point<std::chrono::steady_clock> start_time;
};

#endif // INCLUDE_TICKS_MISSION_PREP_TICK_HPP_