#include <iostream>
#include <thread>
#include <chrono>

#include "camera/mock.hpp"

int main() {
    MockCamera camera;
    int init = camera.getImageCount();

    camera.startTakingPictures(std::chrono::milliseconds(DUMMY_TIMEOUT));
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    camera.stopTakingPictures();

    int post = camera.getImageCount();
    std::cout << "# of images taken:" << post << std::endl;

    return (post > init) ? 0 : 2; 
}

