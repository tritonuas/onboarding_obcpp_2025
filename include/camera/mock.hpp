#ifndef INCLUDE_CAMERA_MOCK_HPP_
#define INCLUDE_CAMERA_MOCK_HPP_

#include <optional>
#include <chrono>
#include <vector>
#include <atomic>
#include <thread>
#include <filesystem>
#include "interface.hpp"
#include "utilities/locks.hpp"

const int DUMMY_INTERVAL = 1000;
const int DUMMY_TIMEOUT = 1000;
const int IMAGE_COUNT = 5;
const std::string images_dir = "/workspaces/onboarding_obcpp_2025/test/images/";

class MockCamera {
    public:

        MockCamera();
        ~MockCamera();

        std::optional<ImageData> takePicture(const std::chrono::milliseconds& timeout);

        void startTakingPictures(const std::chrono::milliseconds& interval);

        void stopTakingPictures();

        // helper function to get the image count
        int getImageCount();

    private:

        std::thread capture_thread;
        std::shared_mutex image_lock;
        std::atomic_bool is_taking_pictures;

        std::vector<ImageData> mock_images;
        std::chrono::time_point<std::chrono::steady_clock> last_taken;

        // helper function to process the optional ImageData
        void processCapturedImage(std::optional<ImageData> capturedImage);

        // helper function to control capturing images at the interval
        void captureInterval(const std::chrono::milliseconds& interval);
};

#endif
