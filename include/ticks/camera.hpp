#ifndef INCLUDE_TICKS_CAMERA_TICK_HPP_
#define INCLUDE_TICKS_CAMERA_TICK_HPP_

#include "ticks/tick.hpp"
#include "camera/mock.hpp"
#include <chrono>

class CameraTick : public Tick {
public:
    explicit CameraTick(std::shared_ptr<MissionState> state);

    void init() override;

    Tick* tick() override;

    std::chrono::milliseconds getWait() const override;

private:
    MockCamera camera;
};

#endif
