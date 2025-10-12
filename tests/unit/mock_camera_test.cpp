#include <gtest/gtest.h>
#include "camera/mock.hpp"

TEST(MockCameraTest, TakePicture) {
    MockCamera cam = MockCamera();
    auto img = cam.takePicture(std::chrono::milliseconds(100));
    EXPECT_TRUE(img.has_value());
    if (img.has_value()) {
        EXPECT_FALSE(img->DATA.empty());
    }
}
