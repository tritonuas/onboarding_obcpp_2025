#include <gtest/gtest.h>
#include <chrono>
#include "camera/mock.hpp"
#include <iostream>

TEST(MockCameraTests, VerifyValueNotEmpty) {
  MockCamera cam;


  std::chrono::milliseconds timeout(600);
  std::optional<ImageData> image = cam.takePicture(timeout);
  EXPECT_TRUE(image.has_value());
  if(image.has_value()) {
    std::cout << "PASS" << std::endl;
  } else {
    std::cout << "FAIL" << std::endl;
  }
}