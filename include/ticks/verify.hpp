#ifndef INCLUDE_TICKS_VERIFY_TICK_HPP_
#define INCLUDE_TICKS_VERIFY_TICK_HPP_

#include "ticks/tick.hpp"
#include <chrono>

/*
 * VerifyTick: The tick that verifies whether the image is valid.
 */
class VerifyTick : public Tick {
public:
    // Constructor that passes the shared state to the base Tick class.
    explicit VerifyTick(std::shared_ptr<MissionState> state);

    // Called once when this tick becomes the active state.
    void init() override;

    // Defines how often the `tick()` method is called.
    std::chrono::milliseconds getWait() const override;

    // The core logic that is executed repeatedly.
    Tick* tick() override;

private:
};

#endif // INCLUDE_TICKS_VERIFY_TICK_HPP_