#pragma once
#include "Aliases.h"

#include <QMainWindow>
#include <QTimer>
#include <opencv2/core/mat.hpp>

DECLARE_QT_CLASS(MainWindow)

extern void* myLabell;
#include <
#include "MultiCameraTracker.h"
#include <QCameraInfo>
class MainWindow : public QMainWindow {
    Q_OBJECT
    QTimer _timer;
    private slots:
    void on_timeout();
public:

    MainWindow(QWidget *parent = nullptr, cv::Mat* img = nullptr);
    ~MainWindow();

private:
    cv::Mat* img;
    MultiCameraTracker multiCameraTracker;
    Ui::MainWindow *ui;
};
