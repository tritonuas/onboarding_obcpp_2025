#ifndef INCLUDE_CAMERA_INTERFACE_HPP_
#define INCLUDE_CAMERA_INTERFACE_HPP_

#include <optional>
#include <opencv2/opencv.hpp>
#include "utilities/base64.hpp"

struct ImageData {
    cv::Mat DATA;
};

std::string cvMatToBase64(cv::Mat image);

class CameraInterface {

    public: 

        explicit CameraInterface() = default;
        virtual ~CameraInterface() = default;

        virtual std::optional<ImageData> takePicture(const std::chrono::milliseconds& timeout) = 0;

        virtual void startTakingPictures(const std::chrono::milliseconds& interval) = 0;

        virtual void stopTakingPictures() = 0;
};

#endif
