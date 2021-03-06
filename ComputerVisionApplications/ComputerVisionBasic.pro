#-------------------------------------------------
#
# Project created by QtCreator 2019-04-18T16:11:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ComputerVisionBasic
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
include(C:/dev/opencv-3.3.0/opencv.pri)

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    filtersdialog.cpp \
    thresholdingdialog.cpp \
    morphologydialog.cpp \
    templatematchingdialog.cpp \
    featuredetectordialog.cpp \
    extrctandmtchdialog.cpp \
    smoothdialog.cpp \
    pyramidsdialog.cpp \
    borderdialog.cpp \
    edgedetectiondialog.cpp \
    imgtransformdialog.cpp \
    houghdialog.cpp \
    imgsegmentationdialog.cpp \
    histogramdialog.cpp

HEADERS += \
        mainwindow.h \
    filtersdialog.h \
    thresholdingdialog.h \
    morphologydialog.h \
    templatematchingdialog.h \
    featuredetectordialog.h \
    extrctandmtchdialog.h \
    smoothdialog.h \
    pyramidsdialog.h \
    borderdialog.h \
    edgedetectiondialog.h \
    imgtransformdialog.h \
    houghdialog.h \
    imgsegmentationdialog.h \
    histogramdialog.h

FORMS += \
        mainwindow.ui \
    filtersdialog.ui \
    thresholdingdialog.ui \
    morphologydialog.ui \
    templatematchingdialog.ui \
    featuredetectordialog.ui \
    extrctandmtchdialog.ui \
    smoothdialog.ui \
    pyramidsdialog.ui \
    borderdialog.ui \
    edgedetectiondialog.ui \
    imgtransformdialog.ui \
    houghdialog.ui \
    imgsegmentationdialog.ui \
    histogramdialog.ui

DISTFILES += \
    Graphics/images2.jpg

