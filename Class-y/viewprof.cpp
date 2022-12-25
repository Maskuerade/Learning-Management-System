#include "viewprof.h"
#include "ui_viewprof.h"

ViewProf::ViewProf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewProf)
{
    ui->setupUi(this);
}

ViewProf::~ViewProf()
{
    delete ui;
}
