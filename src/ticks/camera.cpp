#include <thread>
#include <iostream>
#include "ticks/camera.hpp"
#include "ticks/ids.hpp"
#include "ticks/cvloiter.hpp"
#include "core/mission_state.hpp"

CameraTick::CameraTick(std::shared_ptr<MissionState> state) : Tick(state, TickID::Camera), camera() {

}

void CameraTick::init() {
    std::cout << "Initializing Camera..." << std::endl;
}

Tick* CameraTick::tick() {

        auto maybe_image = this->camera.takePicture(std::chrono::milliseconds(DUMMY_TIMEOUT));
        if (maybe_image.has_value()) {
            state->image = maybe_image;
        } else {
            state->image.reset();
        }

        return new CVLoiterTick(state);

    }


std::chrono::milliseconds CameraTick::getWait() const {
    return std::chrono::milliseconds(250);
}
