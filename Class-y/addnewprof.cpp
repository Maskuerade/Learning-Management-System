#include "addnewprof.h"
#include "ui_addnewprof.h"

Addnewprof::Addnewprof(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Addnewprof)
{
    ui->setupUi(this);
}

Addnewprof::~Addnewprof()
{
    delete ui;
}
