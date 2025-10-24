#include "camera/mock.hpp"
#include <iostream>

int main() {
  MockCamera camera;
  std::chrono::milliseconds timeout(600);
  int valid_count = 0;

  for(int i = 0; i < 5; i++) {
    std::optional<ImageData> image = camera.takePicture(timeout);
    if(std::filesystem::exists(image->filename)) {
      std::cout << "Image exists" << std::endl;
    }
    valid_count++;
  }
  if(valid_count != 5) {
    return -1;
  }
  return 0;
}