#include "addnewstd.h"
#include "ui_addnewstd.h"

addnewstd::addnewstd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addnewstd)
{
    ui->setupUi(this);
}

addnewstd::~addnewstd()
{
    delete ui;
}
