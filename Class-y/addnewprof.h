#ifndef ADDNEWPROF_H
#define ADDNEWPROF_H

#include <QWidget>

namespace Ui {
class Addnewprof;
}

class Addnewprof : public QWidget
{
    Q_OBJECT

public:
    explicit Addnewprof(QWidget *parent = nullptr);
    ~Addnewprof();

private:
    Ui::Addnewprof *ui;
};

#endif // ADDNEWPROF_H
