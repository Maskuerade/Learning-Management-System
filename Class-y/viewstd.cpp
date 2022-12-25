#include "viewstd.h"
#include "ui_viewstd.h"

ViewStd::ViewStd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewStd)
{
    ui->setupUi(this);
}

ViewStd::~ViewStd()
{
    delete ui;
}
