#ifndef CYLINDRICAL_1ST_H
#define CYLINDRICAL_1ST_H

#include <QDialog>
#include <QImage>
#include <QDebug>
#include <QPixmap>
#include <qmath.h>
#include "dialog.h"
#include <QMainWindow>


namespace Ui {
class Cylindrical_1st;
}

class Cylindrical_1st : public QDialog
{
    Q_OBJECT

public:
    explicit Cylindrical_1st(QWidget *parent = 0);

    ~Cylindrical_1st();

signals:
    void sendCylindricalImage(QImage img,int i);

public slots:
    void Recv_Image(QImage img){
        originalImage = img;
    }

    void Recv_len(int recv_len){
        focal_length = recv_len;
    }
    void Recv_Num(int i){
        index = i;
    }

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Cylindrical_1st *ui;
    Dialog *dlg;
    int focal_length = 0;
    int index = 0;
    QImage originalImage;
    QImage projectionImage;
    QPixmap oripix;
    QPixmap propix;
    int Get_New_X_Index(int x, int focal_len, int center_x1, int center_x2);
    int Get_New_Y_Index(int x, int y, int focal_len, int center_y1, int center_y2,int center_x1);
};

#endif // CYLINDRICAL_1ST_H
