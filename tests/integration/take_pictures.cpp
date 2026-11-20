#include <iostream>
#include <thread>
#include <chrono>

#include "camera/mock.hpp"

int main(){
    MockCamera *cam = new MockCamera();
    std::cout << "IMAGES BEFORE TAKING: " << cam->getImageCount();
    cam->startTakingPictures(std::chrono::milliseconds(500));
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    cam->stopTakingPictures();
    std::cout << "IMAGES AFTER TAKING: " << cam->getImageCount();
}