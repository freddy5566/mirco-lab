#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include <sstream>
#include <QString>


using namespace std;
using namespace cv;

VideoCapture cap(0);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->openCameraButton, SIGNAL(clicked()), this, SLOT(OpenCamera()), Qt::AutoConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}
QImage MainWindow::cvMat2QImage(const cv::Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}
void MainWindow::OpenCamera()
{
    std::cout<<"222222";
    ui->openCameraButton->setEnabled(false);
    // open webcam
    std::cout<<"222222";
    if(cap.isOpened())
    {
        while(1)
        {
            cap >> cameraMat;
            QImage img = cvMat2QImage(cameraMat);
            ui->currentlabel->setPixmap(QPixmap::fromImage(img).scaled(ui->currentlabel->size()));
            waitKey(30);
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    imwrite("../Image.jpg", temp);
    this->close();
}

void MainWindow::on_pushButton_2_clicked()
{
    Mat frame;
    cap >> frame;
    QImage showQimg = cvMat2QImage(frame);
    ui->result->setPixmap(QPixmap::fromImage(showQimg));
    temp = frame;
}

void MainWindow::on_pushButton_5_clicked()
{
    Mat frame;
    cvtColor(temp, frame, CV_BGR2GRAY);
    QImage showQimg = cvMat2QImage(frame);
    ui->result->setPixmap(QPixmap::fromImage(showQimg));
    temp = frame;
}

void MainWindow::on_pushButton_6_clicked()
{
    Mat frame;
    threshold(temp, frame, 170, 255, THRESH_BINARY);
    QImage showQimg = cvMat2QImage(frame);
    ui->result->setPixmap(QPixmap::fromImage(showQimg));
    temp = frame;
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    this->blockSize = position;
    stringstream ss;
    string number;
    ss << position;
    ss >> number;

    ui->mosaicLabel->setText(QString::fromStdString("block size: " + number));
}


void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    this->blurSize = position;
    stringstream ss;
    string number;
    ss << position;
    ss >> number;

    ui->blurLabel->setText(QString::fromStdString("blur size: " + number));
}

void MainWindow::on_pushButton_4_clicked()
{
    //blur
    Mat frame;
    blur(temp, frame, Size(this->blurSize/10.0, this->blurSize/10.0));
    QImage showQimg = cvMat2QImage(frame);
    ui->result->setPixmap(QPixmap::fromImage(showQimg));
    temp = frame;
}

void MainWindow::on_pushButton_3_clicked()
{/*
    Mat subMat;
    cameraMat.convertTo(temp, CV_32FC3);

    cout << "dim is " << subMat.dims << endl;

    int n_row = cameraMat.rows;
    int n_col = cameraMat.cols;

    for (int i = blockSize; i < cameraMat.rows - 1 - blockSize; i += blockSize) {
        for (int j = blockSize; j < cameraMat.cols - 1- blockSize; j += blockSize) {

            float k1 = (double)((rand() % 100)) / 100.0 - 0.5;
            float k2 = (double)((rand() % 100)) / 100.0 - 0.5;

            float m = k1 * (blockSize * 2 - 1);
            float n = k2 * (blockSize * 2 - 1);

            int h = (int)(i + m) % n_row;
            int w = (int)(j + n) % n_col;

            subMat = temp.operator()(Range(i - blockSize, i + blockSize), Range(j - blockSize, j+ blockSize));
            subMat.setTo(Scalar(cameraMat.at<Vec3b>(h, w)));

        }
    }

    QImage showQimg = cvMat2QImage(temp);
    ui->result->setPixmap(QPixmap::fromImage(showQimg));*/
}
