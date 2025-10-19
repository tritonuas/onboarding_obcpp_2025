//I already did this test by accident as a unit test
//not sure if there's a point
#include <gtest/gtest.h>
#include <chrono>
#include "camera/mock.hpp"
int main() {
    auto cam = MockCamera();
    int amount = cam.getImageCount();
    auto duration = std::chrono::milliseconds(2000);
    cam.startTakingPictures(duration/10);
    std::this_thread::sleep_for(duration);
    int dif = cam.getImageCount() - amount;
    std::cout << "Change of " << dif  << " expected:10" << std::endl;
    return 0;
}
