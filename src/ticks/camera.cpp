#include "ticks/camera.hpp"
#include "ticks/verify.hpp"

#include <chrono>
#include <iostream>

CameraTick::CameraTick(std::shared_ptr<MissionState> state)
    : Tick(state, TickID::Camera){}

void CameraTick::init() {
    this->camera = new MockCamera();
}

Tick* CameraTick::tick(){
    std::optional<ImageData> img = this->camera->takePicture(std::chrono::milliseconds(DUMMY_TIMEOUT));
    
    state->image = img;

    return new VerifyTick(state);

}

std::chrono::milliseconds CameraTick::getWait() const {
    return std::chrono::milliseconds(250);
}