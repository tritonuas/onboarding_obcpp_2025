#include <gtest/gtest.h>
#include <chrono>

#include "core/mission_state.hpp"
#include "camera/mock.hpp"

using namespace std::chrono_literals;

// Verifies that images_dir points to a real folder with at least one image.
TEST(MissionCameraTest, ImageDirExists) {
    // Loads the image directory specified in hpp
    std::filesystem::path image_dir_path = images_dir;
    
    // Code that retrieves entries from the directory into `entries`
    std::vector<std::filesystem::directory_entry> entries;
    for (auto& entry : std::filesystem::directory_iterator(image_dir_path)) {
        entries.push_back(entry);
    }

    EXPECT_FALSE(entries.empty());
}

TEST(MissionCameraTest, TestTakePicture) {
    // Creates a MockCamera, gets an image w/ timeout 1000 ms
    MockCamera testCamera{}; 
    auto testOutput = testCamera.takePicture(std::chrono::seconds(1));

    /// Checks the returned cv:Mat.DATA value
    EXPECT_FALSE(testOutput.value().DATA.empty());
}

TEST(MissionCameraTest, TestStartCaptureCaptureIntervel) {
    // Start capture protocol, sleep thread, check size.
    MockCamera testCamera{}; 
    testCamera.startTakingPictures(250ms);
    std::this_thread::sleep_for(1100ms);
    EXPECT_EQ(testCamera.getImageCount(), 4);
}
