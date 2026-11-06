#ifndef INCLUDE_TICKS_CAVLOITER_TICK_HPP_
#define INCLUDE_TICKS_CAVLOITER_TICK_HPP_

#include <chrono>
#include <memory>
#include "ticks/ids.hpp"
#include "ticks/tick.hpp"

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
protected:
    std::shared_ptr<MissionState> state;
    TickID id;
};

#endif // INCLUDE_TICKS_CVLOITER_TICK_HPP_