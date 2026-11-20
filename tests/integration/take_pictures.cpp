#include <iostream>

#include "camera/mock.hpp"

int main() {
    MockCamera camera;
    int startingImgCnt = camera.getImageCount();
    std::cout << "Starting image count: " << startingImgCnt << std::endl;
    camera.startTakingPictures(std::chrono::milliseconds(1337));
    std::this_thread::sleep_for(std::chrono::seconds(6));
    camera.stopTakingPictures();
    std::cout << "Camera stopped" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(6));
    int finalImgCnt = camera.getImageCount();
    std::cout << "ending image count: " << finalImgCnt << std::endl;
}