#ifndef INCLUDE_CAMERA_INTERFACE_HPP_
#define INCLUDE_CAMERA_INTERFACE_HPP_

#include <optional>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <string>
#include "utilities/base64.hpp"

// Struct to hold the image
struct ImageData {
    cv::Mat DATA;
    std::string filename;
};

// Utility function for converting an image loaded with OpenCV into base-64
std::string cvMatToBase64(cv::Mat image);

/* 
 * CameraInterface: Abstract interface for camera implementation
 */
class CameraInterface {

    public: 

        // Default constructors and destructors
        explicit CameraInterface() = default;
        virtual ~CameraInterface() = default;

        // Attempts to capture an image within the given timeout
        virtual std::optional<ImageData> takePicture(const std::chrono::milliseconds& timeout) = 0;

        // Begins taking pictures at the specified interval
        virtual void startTakingPictures(const std::chrono::milliseconds& interval) = 0;

        // Stops taking pictures
        virtual void stopTakingPictures() = 0;
};

#endif
