#ifndef VIEWSTD_H
#define VIEWSTD_H

#include <QDialog>

namespace Ui {
class ViewStd;
}

class ViewStd : public QDialog
{
    Q_OBJECT

public:
    explicit ViewStd(QWidget *parent = nullptr);
    ~ViewStd();

private:
    Ui::ViewStd *ui;
};

#endif // VIEWSTD_H
