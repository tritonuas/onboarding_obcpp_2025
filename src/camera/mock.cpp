#include <iostream>
#include <filesystem>
#include "camera/mock.hpp"

MockCamera::MockCamera() : CameraInterface() {

}

MockCamera::~MockCamera() {

}

std::optional<ImageData> MockCamera::takePicture(const std::chrono::milliseconds& timeout) {

    auto start_time = std::chrono::steady_clock::now();

    std::filesystem::path image_dir_path = images_dir;
    
    std::vector<std::filesystem::directory_entry> entries;
    for (auto& entry : std::filesystem::directory_iterator(image_dir_path)) {
        entries.push_back(entry);
    }

    // NOTE: at this point, we have a vector of images from the directory of images we want to load from

    // TODO: load a random image with OpenCV. If the image is loaded within the timeout, return the image in a ImageData struct, otherwise return no image



    return std::nullopt; // placeholder return
}


void MockCamera::startTakingPictures(const std::chrono::milliseconds& interval) {


}

void MockCamera::stopTakingPictures() {


}

void MockCamera::processCapturedImage(std::optional<ImageData> capturedImage) {

}

int MockCamera::getImageCount() {
    return 0; // placeholder return
}

void MockCamera::captureInterval(const std::chrono::milliseconds& interval) {

}

