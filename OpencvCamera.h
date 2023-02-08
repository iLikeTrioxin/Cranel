#pragma once

#include "CranelCamera.h"

class OpenCVCamera : public CranelCamera {
public:
    explicit OpenCVCamera(int cameraId = 0);

    void nextFrame() override;

    ~OpenCVCamera() override = default;

    cv::VideoCapture camera;
};