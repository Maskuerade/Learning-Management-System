#include "prof.h"
#include "ui_prof.h"

prof::prof(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::prof)
{
    ui->setupUi(this);
}

prof::~prof()
{
    delete ui;
}
