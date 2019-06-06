#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    cv::Mat cameraMat;
    Ui::MainWindow *ui;
    QImage cvMat2QImage(const cv::Mat& mat);
    QImage saveImg;
    cv::Mat temp;
    int blurSize = 0;
    int blockSize = 0;

private slots:
    void OpenCamera();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_horizontalSlider_sliderMoved(int position);
    void on_horizontalSlider_2_sliderMoved(int position);
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
};

#endif // MAINWINDOW_H
