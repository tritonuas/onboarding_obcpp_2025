#include "camera/mock.hpp"

int main() {
    MockCamera cam = MockCamera();
    int preImgNum = cam.getImageCount();
    cam.startTakingPictures(std::chrono::milliseconds(100));
    std::this_thread::sleep_for(std::chrono::seconds(5));
    cam.stopTakingPictures();
    int postImgNum = cam.getImageCount();
    std::cout << "Images before: " << preImgNum << '\n';
    std::cout << "Images after: " << postImgNum << '\n';
    if (postImgNum > preImgNum) {
        std::cout << "PASS";
        return 0;
    }
    std::cout << "FAIL";
    return 1;
}
