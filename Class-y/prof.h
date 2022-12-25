#ifndef PROF_H
#define PROF_H

#include <QDialog>

namespace Ui {
class prof;
}

class prof : public QDialog
{
    Q_OBJECT

public:
    explicit prof(QWidget *parent = nullptr);
    ~prof();

private:
    Ui::prof *ui;
};

#endif // PROF_H
