#pragma once

#include <opencv2/opencv.hpp>

class CranelCamera {
public:
    const cv::Mat& getFrame(bool nextFrame = true) {
        if(nextFrame) this->nextFrame();
        return frame;
    }

    virtual void nextFrame() = 0;
    virtual ~CranelCamera() = default;

protected:
    cv::Mat frame;
};