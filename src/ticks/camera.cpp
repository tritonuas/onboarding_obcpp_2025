#include <thread>
#include <iostream>
#include "ticks/camera.hpp"

CameraTick::CameraTick(std::shared_ptr<MissionState> state) : Tick(state), camera() {

}

void CameraTick::init() {
    std::cout << "Initializing Camera..." << std::endl;
}

Tick* CameraTick::tick() {

    this->camera.startTakingPictures(std::chrono::milliseconds(DUMMY_INTERVAL));

    if (this->camera.getImageCount() >= IMAGE_COUNT) {

        std::cout << "Calling stopTakingPictures()" << std::endl;

        this->camera.stopTakingPictures();

        // TODO: not sure what tick to return so just return nullptr
    } else {

        std::cout << this->camera.getImageCount() << std::endl;
        return nullptr;

    }

}

std::chrono::milliseconds CameraTick::getWait() const {
    return std::chrono::milliseconds(250);
}
