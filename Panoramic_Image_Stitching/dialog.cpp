#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_Focal_len_editingFinished()
{
    focal_len = ui->Focal_len->text().toDouble();
}

void Dialog::on_buttonBox_accepted()
{
    connect(this,SIGNAL(sendFocal_len(int)),parent(),SLOT(Recv_len(int)));
    emit sendFocal_len(focal_len);
}

void Dialog::on_buttonBox_rejected()
{
    close();
}
