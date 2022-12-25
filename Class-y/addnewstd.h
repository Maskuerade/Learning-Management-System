#ifndef ADDNEWSTD_H
#define ADDNEWSTD_H

#include <QWidget>

namespace Ui {
class addnewstd;
}

class addnewstd : public QWidget
{
    Q_OBJECT

public:
    explicit addnewstd(QWidget *parent = nullptr);
    ~addnewstd();

private:
    Ui::addnewstd *ui;
};

#endif // ADDNEWSTD_H
