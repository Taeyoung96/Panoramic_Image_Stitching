#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/stitching.hpp"

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Open1st_photo_triggered()
{
    //when you click this button you can choose cy1st[0]
    opendlg(0);

    //to open FileDialog
    //choose the picture
    QString strFilter = "jpg file(*.jpg);;png file(*.png)";
    strFileName = QFileDialog::getOpenFileName(this,"Open a file","C:/Users/TaeYoung/Desktop/Image",strFilter);
    //change QString to std::string
    str[0] = strFileName.toStdString();

    //load image
    originImage[0].load(strFileName);

    //initialize dialog
    cy1st[0] = new Cylindrical_1st(this);

    //to send the image to dialog and index
    connect(this,SIGNAL(sendImage(QImage)),cy1st[0],SLOT(Recv_Image(QImage)));
    connect(this,SIGNAL(sendNumber(int)),cy1st[0],SLOT(Recv_Num(int)));
    emit sendImage(originImage[0]);
    emit sendNumber(0);

    //excute the dialog
    cy1st[0]->setModal(true);
    cy1st[0]->exec();

    //to show the image on QLabel
    firstpix = QPixmap::fromImage(cylindricalImage[index]);
    ui->label->setPixmap(firstpix);
    ui->label->setScaledContents(true);

}

void MainWindow::on_Open2nd_Photo_triggered()
{
    //when you click this button you can choose cy1st[1]
    opendlg(1);

    //to open FileDialog
    //choose the picture
    QString strFilter = "jpg file(*.jpg)";
    strFileName = QFileDialog::getOpenFileName(this,"Open a file","C:/Users/TaeYoung/Desktop/Image",strFilter);
    //change QString to std::string
    str[1] = strFileName.toStdString();
    //load the image
    originImage[1].load(strFileName);

    //initialize the dialog
    cy1st[1] = new Cylindrical_1st(this);

    //to send the image to dialog and index
    connect(this,SIGNAL(sendImage(QImage)),cy1st[1],SLOT(Recv_Image(QImage)));
    connect(this,SIGNAL(sendNumber(int)),cy1st[1],SLOT(Recv_Num(int)));
    emit sendImage(originImage[1]);
    emit sendNumber(1);

    //excute the dialog
    cy1st[1]->setModal(true);
    cy1st[1]->exec();

    firstpix = QPixmap::fromImage(cylindricalImage[index]);
    ui->label_2->setPixmap(firstpix);
    ui->label_2->setScaledContents(true);

}

void MainWindow::on_Open3rd_Photo_triggered()
{
    //when you click this button you can choose cy1st[2]
    opendlg(2);

    //to open FileDialog
    //choose the picture
    QString strFilter = "jpg file(*.jpg)";
    strFileName = QFileDialog::getOpenFileName(this,"Open a file","C:/Users/TaeYoung/Desktop/Image",strFilter);
    //change QString to std::string
    str[2] = strFileName.toStdString();
    //load the image
    originImage[2].load(strFileName);

    //initialize dialog(Cylindrical_3rd)
    cy1st[2] = new Cylindrical_1st(this);

    //to send the image to dialog and index
    connect(this,SIGNAL(sendImage(QImage)),cy1st[2],SLOT(Recv_Image(QImage)));
    connect(this,SIGNAL(sendNumber(int)),cy1st[2],SLOT(Recv_Num(int)));
    emit sendImage(originImage[2]);
    emit sendNumber(2);

    cy1st[2]->setModal(true);
    cy1st[2]->exec();

    firstpix = QPixmap::fromImage(cylindricalImage[index]);
    ui->label_3->setPixmap(firstpix);
    ui->label_3->setScaledContents(true);
}

void MainWindow::on_Open4th_Photo_triggered()
{
    //when you click this button you can choose cy1st[3]
    opendlg(3);

    //to open FileDialog
    //choose the picture
    QString strFilter = "jpg file(*.jpg)";
    strFileName = QFileDialog::getOpenFileName(this,"Open a file","C:/Users/TaeYoung/Desktop/Image",strFilter);
    //change QString to std::string
    str[3] = strFileName.toStdString();
    //load the image
    originImage[3].load(strFileName);

    //initialize dialog
    cy1st[3] = new Cylindrical_1st(this);

    //to send the image to dialog and index
    connect(this,SIGNAL(sendImage(QImage)),cy1st[3],SLOT(Recv_Image(QImage)));
    connect(this,SIGNAL(sendNumber(int)),cy1st[3],SLOT(Recv_Num(int)));
    emit sendImage(originImage[3]);
    emit sendNumber(3);

    cy1st[3]->setModal(true);
    cy1st[3]->exec();

    firstpix = QPixmap::fromImage(cylindricalImage[index]);
    ui->label_4->setPixmap(firstpix);
    ui->label_4->setScaledContents(true);
}

void MainWindow::on_Open5th_Photo_triggered()
{
    //when you click this button you can choose cy1st[4]
    opendlg(4);

    //to open FileDialog
    //choose the picture
    QString strFilter = "jpg file(*.jpg)";
    strFileName = QFileDialog::getOpenFileName(this,"Open a file","C:/Users/TaeYoung/Desktop/Image",strFilter);
    //change QString to std::string
    str[4] = strFileName.toStdString();
    //load the image
    originImage[4].load(strFileName);

    //initialize dialog(Cylindrical_5th)
    cy1st[4] = new Cylindrical_1st(this);

    //to send the image to dialog
    connect(this,SIGNAL(sendImage(QImage)),cy1st[4],SLOT(Recv_Image(QImage)));
    connect(this,SIGNAL(sendNumber(int)),cy1st[4],SLOT(Recv_Num(int)));
    emit sendImage(originImage[4]);
    emit sendNumber(4);

    cy1st[4]->setModal(true);
    cy1st[4]->exec();

    firstpix = QPixmap::fromImage(cylindricalImage[index]);
    ui->label_5->setPixmap(firstpix);
    ui->label_5->setScaledContents(true);
}

void MainWindow::on_Open6th_Photo_triggered()
{
    //when you click this button you can choose cy1st[5]
    opendlg(5);

    //to open FileDialog
    //choose the picture
    QString strFilter = "jpg file(*.jpg)";
    strFileName = QFileDialog::getOpenFileName(this,"Open a file","C:/Users/TaeYoung/Desktop/Image",strFilter);
    //change QString to std::string
    str[5] = strFileName.toStdString();
    //load the image
    originImage[5].load(strFileName);

    //initialize dialog
    cy1st[5] = new Cylindrical_1st(this);

    //to send the image to dialog
    connect(this,SIGNAL(sendImage(QImage)),cy1st[5],SLOT(Recv_Image(QImage)));
    connect(this,SIGNAL(sendNumber(int)),cy1st[5],SLOT(Recv_Num(int)));
    emit sendImage( originImage[5]);
    emit sendNumber(5);

    cy1st[5]->setModal(true);
    cy1st[5]->exec();

    firstpix = QPixmap::fromImage(cylindricalImage[index]);
    ui->label_6->setPixmap(firstpix);
    ui->label_6->setScaledContents(true);
}

void MainWindow::on_KeyDetection_1st_triggered()
{
    //First, you must press the 'Open Image' button
    if(cylindricalImage[0].isNull()){
        QMessageBox::about(this,"Warning","First, you click open image '1st Photo' button.");
        return;
    }

    //when you click this button you can choose keyDct[0]
    openkey(0);

    //initialize dialog
    keyDct[0] = new Keydetection(this);

    //to send the image to dialog and index
    connect(this,SIGNAL(sendImage(QImage)),keyDct[0],SLOT(Recv_Image(QImage)));
    connect(this,SIGNAL(sendNumber(int)),keyDct[0],SLOT(Recv_Num(int)));

    //emit the signal
    emit sendImage(cylindricalImage[0]);
    emit sendNumber(0);

    //excute the dialog
    keyDct[0]->setModal(true);
    keyDct[0]->exec();

}

void MainWindow::on_KeyDetection_2nd_triggered()
{
    //First, you must press the 'Open Image' button
    if(cylindricalImage[1].isNull()){
        QMessageBox::about(this,"Warning","First, you click open image '2nd Photo' button.");
        return;
    }

    //when you click this button you can choose keyDct[1]
    openkey(1);

    //initialize dialog
    keyDct[1] = new Keydetection(this);

    //to send the image to dialog and index
    connect(this,SIGNAL(sendImage(QImage)),keyDct[1],SLOT(Recv_Image(QImage)));
    connect(this,SIGNAL(sendNumber(int)),keyDct[1],SLOT(Recv_Num(int)));

    //emit the signal
    emit sendImage(cylindricalImage[1]);
    emit sendNumber(1);

    //excute the dialog
    keyDct[1]->setModal(true);
    keyDct[1]->exec();


}

void MainWindow::on_KeyDetection_3rd_triggered()
{
    //First, you must press the 'Open Image' button
    if(cylindricalImage[2].isNull()){
        QMessageBox::about(this,"Warning","First, you click open image '3rd Photo' button.");
        return;
    }

    //when you click this button you can choose keyDct[1]
    openkey(2);

    //initialize dialog
    keyDct[2] = new Keydetection(this);

    //to send the image to dialog and index
    connect(this,SIGNAL(sendImage(QImage)),keyDct[2],SLOT(Recv_Image(QImage)));
    connect(this,SIGNAL(sendNumber(int)),keyDct[2],SLOT(Recv_Num(int)));

    //emit the signal
    emit sendImage(cylindricalImage[2]);
    emit sendNumber(2);

    //excute the dialog
    keyDct[2]->setModal(true);
    keyDct[2]->exec();


}

void MainWindow::on_KeyDetection_4th_triggered()
{
    //First, you must press the 'Open Image' button
    if(cylindricalImage[3].isNull()){
        QMessageBox::about(this,"Warning","First, you click open image '4th Photo' button.");
        return;
    }

    //when you click this button you can choose keyDct[1]
    openkey(3);

    //initialize dialog
    keyDct[3] = new Keydetection(this);

    //to send the image to dialog and index
    connect(this,SIGNAL(sendImage(QImage)),keyDct[3],SLOT(Recv_Image(QImage)));
    connect(this,SIGNAL(sendNumber(int)),keyDct[3],SLOT(Recv_Num(int)));

    //emit the signal
    emit sendImage(cylindricalImage[3]);
    emit sendNumber(3);

    //excute the dialog
    keyDct[3]->setModal(true);
    keyDct[3]->exec();
}

void MainWindow::on_KeyDetection_5th_triggered()
{
    //First, you must press the 'Open Image' button
    if(cylindricalImage[4].isNull()){
        QMessageBox::about(this,"Warning","First, you click open image '5th Photo' button.");
        return;
    }

    //when you click this button you can choose keyDct[1]
    openkey(4);

    //initialize dialog
    keyDct[4] = new Keydetection(this);

    //to send the image to dialog and index
    connect(this,SIGNAL(sendImage(QImage)),keyDct[4],SLOT(Recv_Image(QImage)));
    connect(this,SIGNAL(sendNumber(int)),keyDct[4],SLOT(Recv_Num(int)));

    //emit the signal
    emit sendImage(cylindricalImage[4]);
    emit sendNumber(4);

    //excute the dialog
    keyDct[4]->setModal(true);
    keyDct[4]->exec();
}

void MainWindow::on_KeyDetection_6th_triggered()
{
    //First, you must press the 'Open Image' button
    if(cylindricalImage[5].isNull()){
        QMessageBox::about(this,"Warning","First, you click open image '6th Photo' button.");
        return;
    }

    //when you click this button you can choose keyDct[1]
    openkey(5);

    //initialize dialog
    keyDct[5] = new Keydetection(this);

    //to send the image to dialog and index
    connect(this,SIGNAL(sendImage(QImage)),keyDct[5],SLOT(Recv_Image(QImage)));
    connect(this,SIGNAL(sendNumber(int)),keyDct[5],SLOT(Recv_Num(int)));

    //emit the signal
    emit sendImage(cylindricalImage[5]);
    emit sendNumber(5);

    //excute the dialog
    keyDct[5]->setModal(true);
    keyDct[5]->exec();
}

void MainWindow::on_Regist1_2_triggered()
{
    if((**first_keydet_result == -1)|(**second_keydet_result == -1)){
        QMessageBox::about(this,"Warning","First, you click the key point detection of 1st and 2nd photos.");
        return;
    }
    //to make QVector to put matched points
    QVector<QPoint> left_pts_vec;
    QVector<QPoint> right_pts_vec;

    //initialize Dialog
    regi2pic = new Registration_2Pic(this);

    //to send the image to dialog
    connect(this,SIGNAL(sendCylindricalImage(QImage,int)),regi2pic,SLOT(RecvCylImage(QImage,int)));
    emit sendCylindricalImage(cylindricalImage[0],0);
    emit sendCylindricalImage(cylindricalImage[1],1);

    int cnt = 0;
    //to check the matching points
    for(int i = 0;i<cylindricalImage[0].height();i++){
        for(int j = 0;j<cylindricalImage[0].width();j++){
            int target_pixel = 0;
            int get_pixel = 0;
            if(first_keydet_result[i][j]>0){  //if target pixel is available
                target_pixel = first_keydet_result[i][j]/100000;
                //get the target pixel with smaller value
                for(int a = 0;a<cylindricalImage[1].height();a++){
                    for(int b=0;b<cylindricalImage[1].width();b++){
                        if(second_keydet_result[a][b]>0){
                            get_pixel = second_keydet_result[a][b]/100000;
                            //get the get pixel with smaller value
                            if(target_pixel == get_pixel){ //if that pixel value is same
                                int height_Max = i+10;
                                int height_Min = i-10;

                                if((a<height_Max)&&(a>height_Min)){ //check the height
                                    cnt++;

                                    pt_left.setX(j);  pt_left.setY(i);
                                    pt_right.setX(b); pt_right.setY(a);

                                    left_pts_vec.push_back(pt_left);
                                    right_pts_vec.push_back(pt_right);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //to send the image to dialog
    connect(this,SIGNAL(sendVector(QVector<QPoint>,QVector<QPoint>)),regi2pic,SLOT(Recv_Vec(QVector<QPoint>,QVector<QPoint>)));
    emit sendVector(left_pts_vec,right_pts_vec);

    qDebug()<<"matched pixels : "<<cnt;

    //excute the dialog
    regi2pic->setModal(true);
    regi2pic->exec();
}

void MainWindow::on_Blending1_2_triggered()  //excute with opencv library
{
    if(str[0].empty()|str[1].empty()){
        QMessageBox::about(this,"Warning","First, you click the 1st and 2nd Photos.");
        return;
    }
    vector<Mat> images;
    Mat leftImage;
    Mat rightImage;

    leftImage = imread(str[0],IMREAD_COLOR);
    rightImage = imread(str[1],IMREAD_COLOR);

    images.push_back(leftImage);
    images.push_back(rightImage);

    Mat result;

    Stitcher sticher = Stitcher::createDefault();

    int ok = sticher.stitch(images,result);

    //if you complete stitching
    if(ok == sticher.OK){
        //initialize the dialog
        blend[0] = new blending(this);

        //to send Mat to blending dialog
        connect(this,SIGNAL(sendMat(cv::Mat)),blend[0],SLOT(RecvMat(cv::Mat)));
        emit sendMat(result);

        //excute the dialog
        blend[0]->setModal(true);
        blend[0]->exec();
    }

}

void MainWindow::on_Blending1_6_triggered()  //excute with opencv library
{
    if(str[0].empty()|str[1].empty()|str[2].empty()|str[3].empty()|str[4].empty()|str[5].empty()){
        QMessageBox::about(this,"Warning","First, you click the 1st ~ 6th Photos.");
        return;
    }
    //initialize vector and Mat class
    vector<Mat> images;
    Mat firstImage,secondImage,thirdImage,fourthImage,fifthImage,sixthImage;

    //initialize Image with Mat class
    firstImage = imread(str[0],IMREAD_COLOR);
    secondImage = imread(str[1],IMREAD_COLOR);
    thirdImage = imread(str[2],IMREAD_COLOR);
    fourthImage = imread(str[3],IMREAD_COLOR);
    fifthImage = imread(str[4],IMREAD_COLOR);
    sixthImage = imread(str[5],IMREAD_COLOR);

    //push Image with vector, It's important to maintain sequence
    images.push_back(firstImage);
    images.push_back(secondImage);
    images.push_back(thirdImage);
    images.push_back(fourthImage);
    images.push_back(fifthImage);
    images.push_back(sixthImage);

    //initialize Mat class to make result image
    Mat result;
    //initialize stitcher class
    Stitcher sticher = Stitcher::createDefault();

    int ok = sticher.stitch(images,result);
    //if stitching is done,
    if(ok == sticher.OK){
        //initialize the dialog
        blend[4] = new blending(this);

        //to send Mat to blending dialog
        connect(this,SIGNAL(sendMat(cv::Mat)),blend[4],SLOT(RecvMat(cv::Mat)));
        emit sendMat(result);

        //excute the dialog
        blend[4]->setModal(true);
        blend[4]->exec();
    }
}

void MainWindow::on_Blending1_3_triggered()  //excute with opencv library
{
    if(str[0].empty()|str[1].empty()|str[2].empty()){
        QMessageBox::about(this,"Warning","First, you click the 1st ~ 3rd Photos.");
        return;
    }
    //initialize vector and Mat class
    vector<Mat> images;
    Mat firstImage,secondImage,thirdImage;

    //initialize Image with Mat class
    firstImage = imread(str[0],IMREAD_COLOR);
    secondImage = imread(str[1],IMREAD_COLOR);
    thirdImage = imread(str[2],IMREAD_COLOR);


    //push Image with vector, It's important to maintain sequence
    images.push_back(firstImage);
    images.push_back(secondImage);
    images.push_back(thirdImage);


    //initialize Mat class to make result image
    Mat result;
    //initialize stitcher class
    Stitcher sticher = Stitcher::createDefault();

    int ok = sticher.stitch(images,result);
    //if stitching is done,
    if(ok == sticher.OK){
        //initialize the dialog
        blend[1] = new blending(this);

        //to send Mat to blending dialog
        connect(this,SIGNAL(sendMat(cv::Mat)),blend[1],SLOT(RecvMat(cv::Mat)));
        emit sendMat(result);

        //excute the dialog
        blend[1]->setModal(true);
        blend[1]->exec();
    }
}

void MainWindow::on_Blending1_4_triggered()  //excute with opencv library
{
    if(str[0].empty()|str[1].empty()|str[2].empty()|str[3].empty()){
        QMessageBox::about(this,"Warning","First, you click the 1st ~ 4th Photos.");
        return;
    }
    //initialize vector and Mat class
    vector<Mat> images;
    Mat firstImage,secondImage,thirdImage,fourthImage;

    //initialize Image with Mat class
    firstImage = imread(str[0],IMREAD_COLOR);
    secondImage = imread(str[1],IMREAD_COLOR);
    thirdImage = imread(str[2],IMREAD_COLOR);
    fourthImage = imread(str[3],IMREAD_COLOR);


    //push Image with vector, It's important to maintain sequence
    images.push_back(firstImage);
    images.push_back(secondImage);
    images.push_back(thirdImage);
    images.push_back(fourthImage);


    //initialize Mat class to make result image
    Mat result;
    //initialize stitcher class
    Stitcher sticher = Stitcher::createDefault();

    int ok = sticher.stitch(images,result);
    //if stitching is done,
    if(ok == sticher.OK){
        //initialize the dialog
        blend[2] = new blending(this);

        //to send Mat to blending dialog
        connect(this,SIGNAL(sendMat(cv::Mat)),blend[2],SLOT(RecvMat(cv::Mat)));
        emit sendMat(result);

        //excute the dialog
        blend[2]->setModal(true);
        blend[2]->exec();
    }
}

void MainWindow::on_Blending1_5_triggered()  //excute with opencv library
{
    if(str[0].empty()|str[1].empty()|str[2].empty()|str[3].empty()|str[4].empty()){
        QMessageBox::about(this,"Warning","First, you click the 1st ~ 5th Photos.");
        return;
    }
    //initialize vector and Mat class
    vector<Mat> images;
    Mat firstImage,secondImage,thirdImage,fourthImage,fifthImage;

    //initialize Image with Mat class
    firstImage = imread(str[0],IMREAD_COLOR);
    secondImage = imread(str[1],IMREAD_COLOR);
    thirdImage = imread(str[2],IMREAD_COLOR);
    fourthImage = imread(str[3],IMREAD_COLOR);
    fifthImage = imread(str[4],IMREAD_COLOR);


    //push Image with vector, It's important to maintain sequence
    images.push_back(firstImage);
    images.push_back(secondImage);
    images.push_back(thirdImage);
    images.push_back(fourthImage);
    images.push_back(fifthImage);


    //initialize Mat class to make result image
    Mat result;
    //initialize stitcher class
    Stitcher sticher = Stitcher::createDefault();

    int ok = sticher.stitch(images,result);
    //if stitching is done,
    if(ok == sticher.OK){
        //initialize the dialog
        blend[3] = new blending(this);

        //to send Mat to blending dialog
        connect(this,SIGNAL(sendMat(cv::Mat)),blend[3],SLOT(RecvMat(cv::Mat)));
        emit sendMat(result);

        //excute the dialog
        blend[3]->setModal(true);
        blend[3]->exec();
    }
}

void MainWindow::on_Regist1_3_triggered() //just make QMessageBox
{
    QMessageBox::about(this,"Warning","Sorry, Can not implement this algorithm");
    return;
}

void MainWindow::on_Regist1_4_triggered() //just make QMessageBox
{
    QMessageBox::about(this,"Warning","Sorry, Can not implement this algorithm");
    return;
}

void MainWindow::on_Regist1_5_triggered() //just make QMessageBox
{
    QMessageBox::about(this,"Warning","Sorry, Can not implement this algorithm");
    return;
}

void MainWindow::on_Regist1_6_triggered() //just make QMessageBox
{
    QMessageBox::about(this,"Warning","Sorry, Can not implement this algorithm");
    return;
}
