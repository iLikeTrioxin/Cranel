#include "OpencvCamera.h"

OpenCVCamera::OpenCVCamera(int cameraId) {
    camera = cv::VideoCapture(cameraId);
    camera.set(cv::CAP_PROP_EXPOSURE, 0);
}

cv::Mat OpenCVCamera::getFrame() {
    cv::Mat frame;
    camera >> frame;
    return frame;
}