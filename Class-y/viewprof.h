#ifndef VIEWPROF_H
#define VIEWPROF_H

#include <QDialog>

namespace Ui {
class ViewProf;
}

class ViewProf : public QDialog
{
    Q_OBJECT

public:
    explicit ViewProf(QWidget *parent = nullptr);
    ~ViewProf();

private:
    Ui::ViewProf *ui;
};

#endif // VIEWPROF_H
