#include "ticks/camera.hpp"
#include "ticks/cvloiter.hpp"
#include "utilities/locks.hpp"
#include <iostream>
#include <chrono>

CameraTick::CameraTick(std::shared_ptr<MissionState> state) 
        : Tick(state, TickID::Camera) {
    // <3
}

void CameraTick::init()  {

}

Tick* CameraTick::tick() {
    // Lock lock(state->state_mut);
    state->image = camera.takePicture(std::chrono::milliseconds(250));
    // switch to CVLoiter tick
    return new CVLoiterTick(state);
}

std::chrono::milliseconds CameraTick::getWait() const {
    return std::chrono::milliseconds(250);
}