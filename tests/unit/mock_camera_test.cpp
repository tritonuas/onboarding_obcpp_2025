#include <gtest/gtest.h>
#include <chrono>
#include "camera/mock.hpp"
TEST(MockCameraTest, PictureTake){
    auto cam = MockCamera();
    auto photo = cam.takePicture(std::chrono::seconds(1));
    EXPECT_TRUE(photo.has_value());
    EXPECT_FALSE(photo.value().DATA.empty());
}

TEST(MockCameraTest, TestTakingPictures){
    auto cam = MockCamera();
    int amount = cam.getImageCount();
    auto duration = std::chrono::milliseconds(2000);
    cam.startTakingPictures(duration/10);
    std::this_thread::sleep_for(duration);
    int dif = cam.getImageCount() - amount;
    //1 photo of buffer 
    ASSERT_TRUE(dif > 9 && dif < 11);
}