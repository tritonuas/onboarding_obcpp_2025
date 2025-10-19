#ifndef INCLUDE_TICKS_CAMERA_TICK_HPP_
#define INCLUDE_TICKS_CAMERA_TICK_HPP_

#include "ticks/tick.hpp"
#include <chrono>

/*
 * CameraTick: The tick that ends the mission.
 */
class CameraTick : public Tick {
public:
    // Constructor that passes the shared state to the base Tick class.
    explicit CameraTick(std::shared_ptr<MissionState> state);

    // Called once when this tick becomes the active state.
    void init() override;

    // The core logic that is executed repeatedly.
    Tick* tick() override;

    // Defines how often the `tick()` method is called.
    std::chrono::milliseconds getWait() const override;

private:
    std::unique_ptr<class CameraInterface> camera;
};

#endif // INCLUDE_TICKS_CAMERA_TICK_HPP_
