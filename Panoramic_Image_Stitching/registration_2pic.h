#ifndef REGISTRATION_2PIC_H
#define REGISTRATION_2PIC_H

#include <QDialog>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QPainter>
#include <QPointer>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"


namespace Ui {
class Registration_2Pic;
}

class Registration_2Pic : public QDialog
{
    Q_OBJECT

public:
    explicit Registration_2Pic(QWidget *parent = 0);
    ~Registration_2Pic();

public slots:
    void RecvCylImage(QImage img,int i){  //cylindricalImage와 index를 받는다.
        cylindricalImage[i] = img;
        index = i;
    }

    void RecvFirstArray(int ** array){    //첫번째 Result array를 받는다.
        qDebug()<<"1";
        first_keydet_result = array;
    }

    void RecvSecondArray(int ** array){   //두번째 Result array를 받는다.
        qDebug()<<"2";
        second_keydet_result = array;
    }

    void Recv_Vec(QVector<QPoint> vec1, QVector<QPoint> vec2){
        leftVec = vec1;
        rightVec = vec2;
    }

private slots:
    void on_startButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::Registration_2Pic *ui;
    QImage cylindricalImage[2];
    int index;
    QPixmap Imagepix[2];
    QVector<QPoint> leftVec;
    QVector<QPoint> rightVec;
    int ** first_keydet_result;
    int ** second_keydet_result;
};

#endif // REGISTRATION_2PIC_H
