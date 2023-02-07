#pragma once

#include <opencv2/opencv.hpp>

class CranelCamera {
public:
    virtual cv::Mat getFrame() = 0;
    virtual ~CranelCamera() = default;
};