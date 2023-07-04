#ifndef ADDDNEWCOURSE_H
#define ADDDNEWCOURSE_H

#include <QDialog>

namespace Ui {
class adddNewCourse;
}

class adddNewCourse : public QDialog
{
    Q_OBJECT

public:
    explicit adddNewCourse(QWidget *parent = nullptr);
    ~adddNewCourse();

private:
    Ui::adddNewCourse *ui;
};

#endif // ADDDNEWCOURSE_H
