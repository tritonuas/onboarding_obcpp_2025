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

// Mock camera configuration constants, mainly for testing and simulation
const int DUMMY_INTERVAL = 1000;
const int DUMMY_TIMEOUT = 1000;
const int IMAGE_COUNT = 5;
const std::string images_dir = "/workspaces/images/";

/**
 *
 * MockCamera: a mock implementation of CameraInterface
 * Instead of real hardware and taking an image, we simulate the behavior by loading an image from a directory
 *
 */
class MockCamera : public CameraInterface {
    public:

        MockCamera();
        ~MockCamera();

        // Attempts to capture an image within the given timeout
        std::optional<ImageData> takePicture(const std::chrono::milliseconds& timeout);

        // Begins taking pictures at the specified interval
        void startTakingPictures(const std::chrono::milliseconds& interval);

        // Stops taking pictures
        void stopTakingPictures();

        // helper function to get the image count
        int getImageCount();

    private:

        std::thread capture_thread;             // thread that performs the continuous capture of the camera
        std::shared_mutex image_lock;           // lock to prevent concurrent access to mock_images
        std::atomic_bool is_taking_pictures;    // indicates whether or not the camera is currently taking pictures
        std::vector<ImageData> mock_images;     // data structure for the captured images

        // timestamp of the last image captured
        std::chrono::time_point<std::chrono::steady_clock> last_taken; 

        // helper function to process the optional ImageData
        void processCapturedImage(std::optional<ImageData> capturedImage);

        // helper function to control capturing images at the interval
        void captureInterval(const std::chrono::milliseconds& interval);
};

#endif
