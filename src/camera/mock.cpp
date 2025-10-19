#include <iostream>
#include <filesystem>
#include "camera/mock.hpp"
#include <thread>
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

    std::cout << "MockCamera: loading index " << idx << " from path: " << path_str << std::endl;
    auto readfile = cv::imread(path_str);
    // After the image is taken
    auto now = std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time) >= timeout) {
        return {};
    }  

    image_index++;
    ImageData image_data;
    if(readfile.empty()){
        return {};
    }
    image_data.DATA = readfile;
    image_data.filename = entries[idx].path().string();
    

    return image_data;
}

void MockCamera::startTakingPictures(const std::chrono::milliseconds& interval) {
    this->is_taking_pictures = true;
    std::thread thread([this, interval]() { this->captureInterval(interval); });
    thread.detach();
    return;
}

void MockCamera::stopTakingPictures() {
    this->is_taking_pictures = false;
    return; 
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
    while(this->is_taking_pictures){
       processCapturedImage( takePicture(std::chrono::seconds(1)));
         std::this_thread::sleep_for(interval);
    }
}
