#include <iostream>
#include <filesystem>
#include <thread>
#include "camera/mock.hpp"

MockCamera::MockCamera() : CameraInterface() {
    this->is_taking_pictures = false;
}

MockCamera::~MockCamera() {
    
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
        std::cout << "MockCamera: no entries in images_dir, returning empty image" << std::endl;
        return {};
    }

    // Code that randomly decided an file, and the filepath loaded into path_str
    size_t idx = static_cast<size_t>(image_index) % entries.size();
    std::string path_str = entries[idx].path().string();
    // Get name of image without extensions
    std::string img_name = entries[idx].path().stem();
    std::cout << "MockCamera: loading index " << idx << " from path: " << path_str << std::endl;
    
    // TODO: IMPLEMENT YOUR CODE HERE (to load the image)
    
    // load image from path
    cv::Mat img = cv::imread(path_str);
    if (img.empty()) {
        std::cout << "image is empty" << std::endl;
        image_index++;
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
    image_data.DATA = img;
    image_data.filename = img_name;
    return image_data;

}

void MockCamera::startTakingPictures(const std::chrono::milliseconds& interval) {
    // check if camera is already running
    if (this->is_taking_pictures) {
        std::cout << "camera is currently active" << std::endl;
    } else {
        this->is_taking_pictures = true;
        capture_thread = std::thread(&MockCamera::captureInterval, this, interval);
        capture_thread.detach();
    }
}

void MockCamera::stopTakingPictures() {
    this->is_taking_pictures = false;
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
    return mock_images.size();
}

void MockCamera::captureInterval(const std::chrono::milliseconds& interval) {
    auto last_img_time = std::chrono::steady_clock::now();
    while (is_taking_pictures) {
        auto curr_time = std::chrono::steady_clock::now();
        std::chrono::milliseconds elapsed_time = 
            std::chrono::duration_cast<std::chrono::milliseconds>(curr_time-last_img_time);
        // std::cout << "Current time: " << elapsed_time.count() << std::endl;
        if (elapsed_time > interval) {
            processCapturedImage(takePicture(std::chrono::milliseconds(100)));
            std::cout << "MikuBondage! image count:" << getImageCount() << std::endl;
            last_img_time = std::chrono::steady_clock::now();
        } 
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}
