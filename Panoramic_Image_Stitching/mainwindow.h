#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <QDebug>
#include <QPoint>
#include <QVector>

#include "cylindrical_1st.h"
#include "keydetection.h"
#include "registration_2pic.h"
#include "blending.h"

#include <iostream>
#include <string>
#include "opencv2/core.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/stitching.hpp"

using std::string;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void opendlg(int i){cy1st[i];}  //you can use it like a iterator
    void openkey(int i){keyDct[i];} //you can use it like a iterator

signals:
    void sendImage(QImage img); //to give image to cylidrical class
    void sendNumber(int i);     //to give index to cylindrical class
    void sendCylindricalImage(QImage img,int i); //to give image and index to registration class
    void sendArray(int** array);  //to give array and index to registration class
    void sendVector(QVector<QPoint> vec1, QVector<QPoint> vec2);
    void sendMat(cv::Mat resultImg);  //to give Mat to blending class

public slots:
    void RecvCylImage(QImage img,int i){
        cylindricalImage[i] = img;
        index = i;
    }

    void RecvFirstArray(int ** array){
        first_keydet_result = array;
    }

    void RecvSecondArray(int ** array){
        second_keydet_result = array;
    }

private slots:
    void on_Open1st_photo_triggered();

    void on_Open2nd_Photo_triggered();

    void on_Open3rd_Photo_triggered();

    void on_Open4th_Photo_triggered();

    void on_Open5th_Photo_triggered();

    void on_Open6th_Photo_triggered();

    void on_KeyDetection_1st_triggered();

    void on_KeyDetection_2nd_triggered();

    void on_KeyDetection_3rd_triggered();

    void on_KeyDetection_4th_triggered();

    void on_KeyDetection_5th_triggered();

    void on_KeyDetection_6th_triggered();

    void on_Regist1_2_triggered();

    void on_Blending1_2_triggered();

    void on_Blending1_6_triggered();

    void on_Blending1_3_triggered();

    void on_Blending1_4_triggered();

    void on_Blending1_5_triggered();

    void on_Regist1_3_triggered();

    void on_Regist1_4_triggered();

    void on_Regist1_5_triggered();

    void on_Regist1_6_triggered();

private:
    Ui::MainWindow *ui;

    Cylindrical_1st *cy1st[6];
    Keydetection *keyDct[6];
    Registration_2Pic *regi2pic;
    blending *blend[5];

    QImage originImage[6];
    QImage cylindricalImage[6];
    QImage firstcyImage;
    QImage resultImg;
    QPixmap firstpix;
    QPixmap resultpix;
    QString strFileName = "";
    QPoint pt_left;
    QPoint pt_right;

    string str[6];

    int index = 0;
    int ** first_keydet_result;
    int ** second_keydet_result;
};

#endif // MAINWINDOW_H
