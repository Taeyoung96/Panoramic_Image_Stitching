#ifndef BLENDING_H
#define BLENDING_H

#include <QDialog>
#include <QDebug>
#include <QImage>
#include <QPixmap>

#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/stitching.hpp"

namespace Ui {
class blending;
}

class blending : public QDialog
{
    Q_OBJECT

public:
    explicit blending(QWidget *parent = 0);
    ~blending();

public slots:
    void RecvMat(cv::Mat result){  //get Mat class
        resultMat = result;
    }

private slots:
    void on_OpenButton_clicked();

    void on_CloseButton_clicked();

    void on_SaveButton_clicked();

private:
    Ui::blending *ui;
    cv::Mat resultMat;
    cv::Mat bgrTorgbMat;
    QImage resultImg;
    QPixmap resultpix;
};

#endif // BLENDING_H
