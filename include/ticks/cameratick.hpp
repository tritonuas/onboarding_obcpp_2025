

#include "ticks/tick.hpp"
#include <chrono>
#include "camera/interface.hpp"
#include <memory>
/*
 *  Camera Tick:
 */
class CameraTick : public Tick {
public:
    explicit CameraTick(std::shared_ptr<MissionState> state);

    // Called once when this tick becomes the active state.
    void init() override;

    // Defines how often the `tick()` method is called.
    std::chrono::milliseconds getWait() const override;

    // The core logic that is executed repeatedly.
    Tick* tick() override;
    std::unique_ptr<CameraInterface> camera;
};
