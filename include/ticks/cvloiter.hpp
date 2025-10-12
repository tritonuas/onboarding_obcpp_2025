#ifndef INCLUDE_TICKS_CVLOITER_TICK_HPP_
#define INCLUDE_TICKS_CVLOITER_TICK_HPP_

#include "ticks/tick.hpp"
#include <chrono>

/*
 * CVLoiterTick: Loiters until a capture signal is sent from the GCS.
 */
class CVLoiterTick : public Tick {
public:
    // Constructor that passes the shared state to the base Tick class.
    explicit CVLoiterTick(std::shared_ptr<MissionState> state);

    // Defines how often the `tick()` method is called.
    std::chrono::milliseconds getWait() const override;

    // The core logic that is executed repeatedly.
    Tick* tick() override;

private:
};

#endif // INCLUDE_TICKS_CVLOITER_TICK_HPP_
