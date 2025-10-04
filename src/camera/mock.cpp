#include <iostream>
#include <filesystem>
#include "camera/mock.hpp"

MockCamera::MockCamera() : CameraInterface() {
    this->is_taking_pictures = false;
}

MockCamera::~MockCamera() {

}

std::optional<ImageData> MockCamera::takePicture(const std::chrono::milliseconds& timeout) {

    auto start_time = std::chrono::steady_clock::now();
    static int image_index = 0;

    std::filesystem::path image_dir_path = images_dir;
    
    std::vector<std::filesystem::directory_entry> entries;
    for (auto& entry : std::filesystem::directory_iterator(image_dir_path)) {
        entries.push_back(entry);
    }

    // Debug: show how many entries we found
    std::cout << "MockCamera: entries found = " << entries.size() << std::endl;

    if (entries.empty()) {
        std::cout << "MockCamera: no entries in images_dir, returning empty image" << std::endl;
        return {};
    }

    size_t idx = static_cast<size_t>(image_index) % entries.size();
    std::string path_str = entries[idx].path().string();
    std::cout << "MockCamera: loading index " << idx << " from path: " << path_str << std::endl;
    cv::Mat captured_image = cv::imread(path_str);
    image_index++;

    auto now = std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time) >= timeout) {
        return {};
    }

    if (captured_image.empty()) {
        std::cout << "MockCamera: imread returned empty image for path: " << path_str << std::endl;
        return {};
    }

    ImageData image_data;
    image_data.DATA = captured_image;
    image_data.filename = entries[idx].path().stem().string();

    return image_data;
}

void MockCamera::startTakingPictures(const std::chrono::milliseconds& interval) {
    if (this->is_taking_pictures) {
        return;
    }
    
    this->is_taking_pictures = true;
    this->capture_thread = std::thread(&MockCamera::captureInterval, this, interval);

}

void MockCamera::stopTakingPictures() {

    if (!this->is_taking_pictures) {
        return;
    }

    this->is_taking_pictures = false;
    this->capture_thread.join();

}

void MockCamera::processCapturedImage(std::optional<ImageData> capturedImage) {
    WriteLock lock(this->image_lock);
    if (capturedImage.has_value()) {
        ImageData image = capturedImage.value();

        this->mock_images.push_back(image);
    }
}

int MockCamera::getImageCount() {
    ReadLock lock(this->image_lock);
    
    return this->mock_images.size();
}

void MockCamera::captureInterval(const std::chrono::milliseconds& interval) {

    if (!this->is_taking_pictures) {
        this->is_taking_pictures = true;

        // take a picture
        this->last_taken = std::chrono::steady_clock::now();
        processCapturedImage(takePicture(std::chrono::milliseconds(DUMMY_TIMEOUT)));
    }

    // Note: the way this is written guarantees that a picture is taken at least every interval seconds, not that a picture is taken exactly every interval seconds
    while (this->is_taking_pictures) {

        auto now = std::chrono::steady_clock::now();
        auto elapsed = now - this->last_taken;

        if (std::chrono::duration_cast<std::chrono::milliseconds>(elapsed) >= interval) {
            std::optional<ImageData> captured_image = takePicture(std::chrono::milliseconds(DUMMY_TIMEOUT));

            processCapturedImage(captured_image);

            this->last_taken = std::chrono::steady_clock::now();
        } else {
            std::this_thread::sleep_for(interval - elapsed);
        }

    }

}
