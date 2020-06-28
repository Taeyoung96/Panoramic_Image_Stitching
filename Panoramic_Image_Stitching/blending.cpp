#include "blending.h"
#include "ui_blending.h"

blending::blending(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::blending)
{
    ui->setupUi(this);
}

blending::~blending()
{
    delete ui;
}

void blending::on_OpenButton_clicked()
{
    //to change BGR to RGB because qt Image read RGB color
    cv::cvtColor(resultMat,bgrTorgbMat,CV_BGR2RGB);

    //initialize Qimage belongs to cv::mat
    resultImg = QImage(bgrTorgbMat.data,bgrTorgbMat.cols,bgrTorgbMat.rows,bgrTorgbMat.step,QImage::Format_RGB888);

    //to show the image on QLabel
    resultpix = QPixmap::fromImage(resultImg);
    ui->ImageLabel->setPixmap(resultpix);
    ui->ImageLabel->setScaledContents(true);
}

void blending::on_CloseButton_clicked()
{
    close();
}

void blending::on_SaveButton_clicked()
{
    //to save QImage to jpg  , select the pile path and format
    bool b = resultImg.save("C:/Users/TaeYoung/Desktop/Image/BlendingImage.jpg","JPG");

    Q_ASSERT(b);
}
