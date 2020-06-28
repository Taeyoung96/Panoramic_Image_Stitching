#-------------------------------------------------
#
# Project created by QtCreator 2020-05-21T21:50:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Panoramic_Image_Stitching
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    cylindrical_1st.cpp \
    dialog.cpp \
    keydetection.cpp \
    registration_2pic.cpp \
    blending.cpp

HEADERS  += mainwindow.h \
    cylindrical_1st.h \
    dialog.h \
    keydetection.h \
    registration_2pic.h \
    blending.h

FORMS    += mainwindow.ui \
    cylindrical_1st.ui \
    dialog.ui \
    keydetection.ui \
    registration_2pic.ui \
    blending.ui

INCLUDEPATH += C:\opencv-3.4.3\build\include

LIBS += C:\Qt\QtBuild\bin\libopencv_core343.dll
LIBS += C:\Qt\QtBuild\bin\libopencv_highgui343.dll
LIBS += C:\Qt\QtBuild\bin\libopencv_imgcodecs343.dll
LIBS += C:\Qt\QtBuild\bin\libopencv_imgproc343.dll
LIBS += C:\Qt\QtBuild\bin\libopencv_features2d343.dll
LIBS += C:\Qt\QtBuild\bin\libopencv_calib3d343.dll
LIBS += C:\Qt\QtBuild\bin\libopencv_stitching343.dll
