#ifndef INCLUDE_CAMERA_INTERFACE_HPP_
#define INCLUDE_CAMERA_INTERFACE_HPP_

#include <opencv2/opencv.hpp>
#include "utilities/base64.hpp"

struct ImageData {
    cv::Mat DATA;
};

std::string cvMatToBase64(cv::Mat image);

#endif
