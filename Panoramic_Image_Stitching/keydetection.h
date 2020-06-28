#ifndef KEYDETECTION_H
#define KEYDETECTION_H

#include <QDialog>
#include <QImage>
#include <QDebug>
#include <QPixmap>
#include <QVector>
#include <QPainter>
#include <QGraphicsPixmapItem>


namespace Ui {
class Keydetection;
}

class Keydetection : public QDialog
{
    Q_OBJECT

public:
    explicit Keydetection(QWidget *parent = 0);
    ~Keydetection();

signals:
    void sendArray(int** array);

public slots:
    void Recv_Image(QImage img){
        cylindricalImage = img;
    }
    void Recv_Num(int i){
        index = i;
    }

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Keydetection *ui;
    QImage cylindricalImage;
    QImage blurImage;
    QPixmap pix;
    QColor new_rgb;
    QColor gray;
    QGraphicsPixmapItem item;

    QVector<int> x_store;
    QVector<int> y_store;

    int ** _dx;
    int ** _dy;
    int ** thresh_result;
    int ** nonMax_result;
    int wei = 0;
    int hei = 0;
    int index = 0;
    int cnt = 0;
    int cnt_non = 0;

    void GaussianFilter();
    void dx_gradient();
    void dy_gradient();
    void Calculate_window();
    void Paint(int **arr);
    void nonMaximumSuppression();

    QVector<int> Get_window_dx(int i, int j);
    QVector<int> Get_window_dy(int i, int j);

    int** Padding(QImage blurImage, int width, int height, int paddingSize);
    int** paddingArray(int ** arr2D, int width, int height, int paddingSize);

};

#endif // KEYDETECTION_H
