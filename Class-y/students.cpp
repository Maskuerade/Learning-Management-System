#include "students.h"
#include "ui_students.h"

Students::Students(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Students)
{
    ui->setupUi(this);
}

Students::~Students()
{
    delete ui;
}
