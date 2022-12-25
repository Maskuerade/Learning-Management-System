#ifndef STUDENTS_H
#define STUDENTS_H

#include <QDialog>

namespace Ui {
class Students;
}

class Students : public QDialog
{
    Q_OBJECT

public:
    explicit Students(QWidget *parent = nullptr);
    ~Students();

private:
    Ui::Students *ui;
};

#endif // STUDENTS_H
