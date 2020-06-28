#include "choosefocallength.h"
#include "ui_choosefocallength.h"

chooseFocalLength::chooseFocalLength(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooseFocalLength)
{
    ui->setupUi(this);
}

chooseFocalLength::~chooseFocalLength()
{
    delete ui;
}
