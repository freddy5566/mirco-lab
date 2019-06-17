#-------------------------------------------------
#
# Project created by QtCreator 2019-06-17T15:02:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
INCLUDEPATH += /usr/local/include \
               /usr/local/include/opencv\
               /usr/local/include/opencv2

LIBS +=/usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_core.so\
        /usr/local/lib/libopencv_imgproc.so\
        /usr/local/lib/libopencv_video.so \
        /usr/local/lib/libopencv_objdetect.so
