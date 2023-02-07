#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <iostream>

#include <thread>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "CranelCamera.h"
#include "TrackingDevice.h"
#include "CameraTracker.h"
#include "MyBracelet.h"
#include "KinectCamera.h"
#include "OpencvCamera.h"
#include <string>

cv::Mat contourImage;

void test(){
    auto cam = OpenCVCamera(1);
    while (true){
        contourImage = cam.getFrame();
    }
    return;
    CranelCamera* camera = (CranelCamera*) new KinectCamera();
    CameraTracker tracker(camera);
    TrackingDevice* device = new MyBraclet();

    while(true) {
        tracker.update(device);
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();

    for (const QString &locale : uiLanguages) {
        const QString baseName = "Cranel_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    std::thread t(test);

    MainWindow w(nullptr, &contourImage);
    w.show();
    a.exec();


//    wypierdalaj();
    t.join();
    return 0;
}
