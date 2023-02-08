#include "OpencvCamera.h"

OpenCVCamera::OpenCVCamera(int cameraId) {
    camera = cv::VideoCapture(cameraId);
    camera.set(cv::CAP_PROP_EXPOSURE, 0);
}

void OpenCVCamera::nextFrame() {
    camera >> this->frame;
}