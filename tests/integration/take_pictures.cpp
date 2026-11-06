#include <iostream>
#include <thread>
#include <chrono>

#include <httplib.h>

#include "core/mission_state.hpp"
#include "camera/mock.hpp"
#include "network/gcs.hpp"

using namespace std::chrono_literals;

int main() {
    MockCamera testCamera{};
    std::cout << "Number of Images Before: " << testCamera.getImageCount() << std::endl;
    testCamera.startTakingPictures(250ms);
    std::this_thread::sleep_for(1100ms);
    std::cout << "Number of Images After: " << testCamera.getImageCount() << std::endl;
}

