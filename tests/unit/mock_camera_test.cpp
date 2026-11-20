#include <gtest/gtest.h>
#include <chrono>

#include "camera/mock.hpp"

// Construct Camera and take a picture
TEST(MockCameraTest, TakePicture) {
    MockCamera *cam = new MockCamera();
    std::optional<ImageData> img = cam->takePicture(std::chrono::milliseconds(DUMMY_TIMEOUT));

    EXPECT_FALSE(&img == nullptr);

}

// Take 5 pictures and verify image count is updated properly
TEST(MockCameraTest, imageCount){
    MockCamera *cam = new MockCamera();
    
    for(int i = 0; i < 5; ++i){
        std::optional<ImageData> img = cam->takePicture(std::chrono::milliseconds(DUMMY_TIMEOUT));

        EXPECT_FALSE(&img == nullptr);
    }

    EXPECT_EQ(cam->getImageCount(), 5);
}