#include "ticks/camera.hpp"
#include "camera/mock.hpp"
#include "core/mission_state.hpp"
#include "ticks/cvloiter.hpp"

CameraTick::CameraTick(std::shared_ptr<MissionState> state) : Tick(state, TickID::Camera)
{
    camera = std::make_unique<MockCamera>();
}

void CameraTick::init()
{

}

Tick *CameraTick::tick()
{
    std::lock_guard<std::mutex> imageLock(state->image_mut);
    state->image = camera->takePicture(std::chrono::milliseconds(100));
    return new CVLoiterTick(state);
}

std::chrono::milliseconds CameraTick::getWait() const
{
    return std::chrono::milliseconds();
}
