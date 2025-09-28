#include "camera/interface.hpp"

std::string cvMatToBase64(cv::Mat image) {
    std::vector<uchar> buf;
    cv::imencode(".jpg", image, buf);
    auto *enc_msg = reinterpret_cast<unsigned char*>(buf.data());
    return base64_encode(enc_msg, buf.size());
}
