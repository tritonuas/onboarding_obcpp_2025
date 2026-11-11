#include "core/obc.hpp"
#include "camera/mock.hpp"
int main() {
    MockCamera camera;
    char buffer[69420];
    camera.startTakingPictures(std::chrono::milliseconds(1337));
    std::cin >> buffer;
    return 0;
}