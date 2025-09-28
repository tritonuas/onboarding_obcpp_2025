#include <iostream>
#include <filesystem>
#include "camera/mock.hpp"

MockCamera::MockCamera() : CameraInterface() {

}

MockCamera::~MockCamera() {

}

std::optional<ImageData> MockCamera::takePicture(const std::chrono::milliseconds& timeout) {

    auto start_time = std::chrono::steady_clock::now();
    static int image_index = 0;

    // load the image
    std::filesystem::path image_dir_path = images_dir;
    
    std::vector<std::filesystem::directory_entry> entries;
    for (auto& entry : std::filesystem::directory_iterator(image_dir_path)) {
        entries.push_back(entry);
    }

    cv::Mat captured_image = cv::imread(entries[image_index].path().string());
    image_index++; // 


}

void MockCamera::startTakingPictures(const std::chrono::milliseconds& interval) {


}

void MockCamera::stopTakingPictures() {


}

void MockCamera::processCapturedImage(std::optional<ImageData> capturedImage) {

}

int MockCamera::getImageCount() {

}

void MockCamera::captureInterval(const std::chrono::milliseconds& interval) {

}

