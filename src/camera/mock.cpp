#include <iostream>
#include <filesystem>
#include "camera/mock.hpp"

MockCamera::MockCamera() : CameraInterface() {
    this->is_taking_pictures = false;
}

MockCamera::~MockCamera() {
    stopTakingPictures();
}

std::optional<ImageData> MockCamera::takePicture(const std::chrono::milliseconds& timeout) {

    auto start_time = std::chrono::steady_clock::now();
    static int image_index = 0;

    // Loads the image directory specified in hpp
    std::filesystem::path image_dir_path = images_dir;
    
    // Code that retrieves entries from the directory into `entries`
    std::vector<std::filesystem::directory_entry> entries;
    for (auto& entry : std::filesystem::directory_iterator(image_dir_path)) {
        entries.push_back(entry);
    }

    if (entries.empty()) {
        std::cout << "MockCamera: no     in images_dir, returning empty image" << std::endl;
        return {};
    }

    // Code that randomly decided an file, and the filepath loaded into path_str
    size_t idx = static_cast<size_t>(image_index) % entries.size();
    std::string path_str = entries[idx].path().string();

    std::cout << "MockCamera: loading index " << idx << " from path: " << path_str << std::endl;
    
    // TODO: IMPLEMENT YOUR CODE HERE (to load the image)
    cv::Mat image = cv::imread(path_str);
    if (image.empty()) {
        return {};
    }
      
    // After the image is taken
    auto now = std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time) >= timeout) {
        return {};
    }  

    image_index++;
    ImageData image_data;

    // TODO: IMPLEMENT YOUR CODE HERE (To set the contents of image_data)
    image_data.DATA = image;
    image_data.filename = path_str;
    return image_data;
}

void MockCamera::startTakingPictures(const std::chrono::milliseconds& interval) {
    if (is_taking_pictures.exchange(true)) {
        return; 
    }

    last_taken = std::chrono::steady_clock::now();
    capture_thread = std::thread([this, interval]() {
        captureInterval(interval);
    });
}

void MockCamera::stopTakingPictures() {
    is_taking_pictures.store(false);

    if (capture_thread.joinable()) {
        capture_thread.join();
    }
}

void MockCamera::processCapturedImage(std::optional<ImageData> capturedImage) {
    WriteLock lock(this->image_lock);
    if (capturedImage.has_value()) {
        ImageData image = capturedImage.value();

        this->mock_images.push_back(image);
    }
}

int MockCamera::getImageCount() {
    WriteLock lock(this->image_lock);
    return (this->mock_images.size());
}

void MockCamera::captureInterval(const std::chrono::milliseconds& interval) {
    auto now = std::chrono::steady_clock::now();
    auto next_capture = last_taken + interval;

    while (is_taking_pictures.load()) {
        std::this_thread::sleep_until(next_capture);

        if (!is_taking_pictures.load()) {
            break;
        }

        processCapturedImage(takePicture(interval));
        next_capture += interval;
    }

    return;
}
