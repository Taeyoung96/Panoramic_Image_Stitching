#include "registration_2pic.h"
#include "ui_registration_2pic.h"

Registration_2Pic::Registration_2Pic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration_2Pic)
{
    ui->setupUi(this);
}

Registration_2Pic::~Registration_2Pic()
{
    delete ui;
}

void Registration_2Pic::on_startButton_clicked()
{
    //to update right vector's value
    for(int i =0;i<rightVec.size();i++)
    {
        int x = rightVec.at(i).x() + cylindricalImage[0].width();
        QPoint temp = rightVec.at(i);
        temp.setX(x);
        rightVec[i] = temp;
    }

    //initialize result image
    int result_hei = cylindricalImage[0].height();
    int result_wid = cylindricalImage[0].width() + cylindricalImage[1].width();
    QImage result = QImage(result_wid,result_hei,QImage::Format_RGB888);

    //initialize qpainter
    QPainter painter(&result);
    painter.drawImage(0,0,cylindricalImage[0]);
    painter.drawImage(cylindricalImage[0].width(),0,cylindricalImage[1]);

    //draw line with qpainter
    QPen pen(Qt::red);
    painter.setPen(pen);
    for(int i = 0;i<leftVec.size();i++){
        painter.drawLine(leftVec[i],rightVec[i]);
    }

    //to show result image with Qlabel
    Imagepix[0] = QPixmap::fromImage(result);
    ui->firstPicture->setPixmap(Imagepix[0]);
    ui->firstPicture->setScaledContents(true);

}

void Registration_2Pic::on_closeButton_clicked()
{
    close();
}
