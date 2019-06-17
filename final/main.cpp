#define SYSFS_GPIO_DTR "/sys/class/gpio"
#include "opencv2/video/tracking.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/opencv.hpp>

#include <iostream>
#include <sstream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>


using namespace cv;
using namespace std;
// char check = 's';
int p = 0;

string face_cascade_name = "/home/ubuntu/test/haarcascade_frontalface_alt2.xml";

    // 眼睛特徵庫檔案位置
string eyes_cascade_name = "/home/ubuntu/test/haarcascade_eye_tree_eyeglasses.xml";

    // 用於臉部的CascadeClassifier
CascadeClassifier face_cascade;

    // 用於眼睛的CascadeClassifier
CascadeClassifier eyes_cascade;

    // 視窗名稱
string window_name = "Capture - Face detection";

void write(char *device, char *status) {
    char path[128] = "/dev/";
    strcat(path, device);

    FILE *fp = fopen(path, "w+");

    if (fp == NULL) {
        printf("can't open device!\n");
        return;
    }

    if (!strcmp(status, "on")) {
        fwrite("1", sizeof("1"), 1, fp);
    }
    if (!strcmp(status, "off")) {
        fwrite("0", sizeof("0"), 1, fp);
    }
    fclose(fp);
}

void detectAndDisplay(Mat frame) {
    int tmp = 0;
    int height;
    int width;
    std::vector<Rect> faces;
    Mat frame_gray;
    // Mat frame_a = frame.clone();
    // Mat frame_b = frame.clone();
    height = frame_gray.rows;
    width = frame_gray.cols*frame.channels();
    cvtColor(frame, frame_gray, CV_BGR2GRAY);

    // 直條圖等化
    equalizeHist(frame_gray, frame_gray);
    // 偵測臉部特徵

    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
    cout << "faces size: " << faces.size() << endl;

    for (size_t i = 0; i < faces.size(); i++) {
        Point center(faces[i].x + faces[i].width * 0.5, faces[i].y + faces[i].height * 0.5);
        // 畫出臉部位置
        ellipse(frame, center, Size(faces[i].width * 0.5, faces[i].height * 0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
        // 從影像中擷取出ROI
        Mat faceROI = frame_gray(faces[i]);
        // imshow("456",faceROI);
        std::vector<Rect> eyes;
        // 偵測每個臉的眼睛
        eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
        // 畫出眼睛的位置
        for (size_t j = 0; j < eyes.size(); j++) {
          Point center(faces[i].x + eyes[j].x + eyes[j].width * 0.5, faces[i].y + eyes[j].y + eyes[j].height * 0.5);
          int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
          circle(frame, center, radius, Scalar(255, 0, 0), 4, 8, 0);

        }
    }
    int i = faces.size();
    if(i == 0){
            cout << "0" << endl;
            write("led1","off");
            write("led2","off");
            write("led3","off");
            write("led4","off");
        }
        else if(i == 1){
            cout << "1" << endl;
            write("led1","off");
            write("led2","off");
            write("led3","off");
            write("led4","on");
        }
        else if(i == 2){
            cout << "2" << endl;
            write("led1","off");
            write("led2","off");
            write("led3","on");
            write("led4","on");
        }
        else if(i == 3){
            cout << "3" << endl;
            write("led1","off");
            write("led2","on");
            write("led3","on");
            write("led4","on");
        }
        else if(i == 4){
            cout << "4" << endl;
            write("led1","on");
            write("led2","on");
            write("led3","on");
            write("led4","on");
        }
    string number;
    stringstream ss;

    ss << i * 10;
    ss >> number;


    string scoreString = string("final exam add ") + number + string(" points for team 26!!!!!!");

    putText(frame, scoreString, cvPoint(25, 120), FONT_HERSHEY_DUPLEX, 0.8, Scalar(128));
    imshow(window_name, frame);

    // imshow("123", frame_gray);
}


int main(int argc, const char** argv)
{
    VideoCapture cap(p);
    Mat frame;
    // Load the cascades
    if (!face_cascade.load(face_cascade_name)) {
        cout << "--(!)Error loading" << endl;
    };
    if (!eyes_cascade.load(eyes_cascade_name)) {
        cout << "--(!)Error loading" << endl;
    };
    if(cap.isOpened()){
        while (true) {
            cap >> frame;
            // Apply the classifier to the frame
            if (frame.empty()) {
                cout << " --(!) No captured frame -- Break!";
                continue;
            }
            detectAndDisplay(frame);
            waitKey(30);
        }
    }

    return 0;
}
