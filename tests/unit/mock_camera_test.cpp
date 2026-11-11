#include <gtest/gtest.h>
#include <chrono>

#include "camera/mock.hpp"
// check if the image and underlying matrix is nonempty
TEST(MockCameraTest, CheckImageNotEmpty) {
    MockCamera camera;
    std::optional<ImageData> img = camera.takePicture(std::chrono::milliseconds(250));
    EXPECT_TRUE(img.has_value());
    EXPECT_FALSE(img.value().DATA.empty());
}
// TEST(MockCameraTest, TestImageCount) {
//     MockCamera camera;
//     EXPECT_EQ(0, camera.getImageCount());
//     camera.takePicture(std::chrono::milliseconds(250));
//     EXPECT_EQ(1, camera.getImageCount());
//     camera.takePicture(std::chrono::milliseconds(250));
//     EXPECT_EQ(2, camera.getImageCount());
// }



TEST(MockCameraTest, CheckStartStopTakingPictures) {
    MockCamera camera;
    camera.startTakingPictures(std::chrono::milliseconds(250));
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    camera.stopTakingPictures();
    EXPECT_GE(3, camera.getImageCount());
}