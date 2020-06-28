#include "cylindrical_1st.h"
#include "ui_cylindrical_1st.h"

Cylindrical_1st::Cylindrical_1st(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cylindrical_1st)
{
    ui->setupUi(this);
}

Cylindrical_1st::~Cylindrical_1st()
{
    delete ui;
}

void Cylindrical_1st::on_pushButton_clicked()
{ 
   //to open dialog and choose focal length
   dlg = new Dialog(this);
   dlg->setModal(true);
   dlg->exec();

   //to show original image
   oripix = QPixmap::fromImage(originalImage);
   ui->label->setPixmap(oripix);
   ui->label->setScaledContents(true);

   //to initialize projection image
   int wid = originalImage.width();
   int hei = originalImage.height();
   projectionImage= QImage(wid,hei,QImage::Format_RGB888);
   projectionImage.fill(0);

   //to initialize center x,y
   int pro_center_x = projectionImage.width()/2;
   int pro_center_y = projectionImage.height()/2;

   int ori_center_x = originalImage.width() /2;
   int ori_center_y = originalImage.height() /2;

   //to calculate inverse warping
   for(int i=0; i<projectionImage.height();i++){
       for(int j=0; j<projectionImage.width();j++){
           int get_x = Get_New_X_Index(j,focal_length,pro_center_x,ori_center_x);
           int get_y = Get_New_Y_Index(get_x,i,focal_length,pro_center_y,ori_center_y,pro_center_x);

           //inverse wraping
           if((get_x > -1) && (get_x < originalImage.width()) &&(get_y > -1) && (get_y < originalImage.height())){
               QColor clrCurrent(originalImage.pixel(get_x,get_y));
               projectionImage.setPixelColor(j,i,clrCurrent);
           }
       }
   }

   //to show projection image
   propix = QPixmap::fromImage(projectionImage);
   ui->projection_Image->setPixmap(propix);
   ui->projection_Image->setScaledContents(true);

}

//to calculate x Coordinate
int Cylindrical_1st::Get_New_X_Index(int x, int focal_len, int center_x1, int center_x2)
{
    double new_x;
    double dif_to_center = (double)x - (double)center_x1;

    new_x = (focal_len * tan(dif_to_center/focal_len)) + center_x2;

    return (int) new_x;
}

//to calculate y Coordinate
int Cylindrical_1st::Get_New_Y_Index(int x, int y, int focal_len, int center_y1, int center_y2, int center_x1)
{
    double new_y;
    double dif_to_center_y = (double)y - (double)center_y1;
    double dif_to_center_x = (double)x - (double)center_x1;

    new_y = ((dif_to_center_y * (sqrt(pow(dif_to_center_x,2)+pow(focal_len,2))))/focal_len) + center_y2;

    return (int) new_y;
}

void Cylindrical_1st::on_pushButton_2_clicked()
{
    //send cylindrical image to mainwindow
    connect(this,SIGNAL(sendCylindricalImage(QImage,int)),parent(),SLOT(RecvCylImage(QImage,int)));
    emit sendCylindricalImage(projectionImage,index);

    close();
}
