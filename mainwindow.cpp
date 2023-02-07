#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QApplication>
#include <QMainWindow>
#include <QDebug>

void* myLabell;

QComboBox* cameraSel = nullptr;
#include <iostream>
void callb(){
    std::cout<<"click\n";

}

MainWindow::MainWindow(QWidget *parent, cv::Mat* img)
    : QMainWindow(parent), _timer(this), img(img)
    , ui(new Ui::MainWindow)
{
    connect(&_timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
    ui->setupUi(this);
    // populate your window with images, labels, etc. here

    connect(ui->cameraSub, &QPushButton::pressed, &callb);
    cameraSel = ui->cameraSel;

    _timer.start(10 /*call the timer every 10 ms*/);
}

MainWindow::~MainWindow() {
    delete ui;
}
#include <opencv2/opencv.hpp>
QPixmap cvMatToQPixmap(const cv::Mat &mat) {
    if(mat.empty()) return QPixmap();

    QImage::Format format;
    switch (mat.type()) {
        case CV_8UC1:
            format = QImage::Format_Grayscale8;
            break;
        case CV_8UC3:
            format = QImage::Format_RGB888;
            break;
        default:
            format = QImage::Format_Invalid;
            break;
    }

    QImage image(
            mat.data,
            mat.cols,
            mat.rows,
            static_cast<int>(mat.step),
            format
    );

    if (format == QImage::Format_Invalid) {
        // Handle the error
        return QPixmap();
    }

    if (format == QImage::Format_RGB888) {
        return QPixmap::fromImage(image.rgbSwapped());
    } else {
        return QPixmap::fromImage(image);
    }
}

void MainWindow::on_timeout() {

    ui->beka->setPixmap(cvMatToQPixmap(*this->img));
}

