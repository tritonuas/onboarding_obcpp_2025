#include <gtest/gtest.h>
#include <chrono>

#include "camera/mock.hpp"

TEST(MockCameraTest, FilePathValid) {
    MockCamera camera;

    std::vector<std::filesystem::directory_entry> entries;
    for (auto& entry : std::filesystem::directory_iterator(images_dir)) {
        entries.push_back(entry);
    }

    // Expect set filepath has images
    EXPECT_FALSE(entries.empty());
}

TEST(MockCameraTest, TestTakingPicture) {
    MockCamera camera;

    std::optional<ImageData> img = camera.takePicture(std::chrono::milliseconds(DUMMY_TIMEOUT));
    EXPECT_TRUE(img.has_value());
}
