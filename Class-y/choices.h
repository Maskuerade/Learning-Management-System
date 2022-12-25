#ifndef CHOICES_H
#define CHOICES_H

#include <QDialog>

namespace Ui {
class choices;
}

class choices : public QDialog
{
    Q_OBJECT

public:
    explicit choices(QWidget *parent = nullptr);
    ~choices();

private:
//    Ui::choices *ui;
};

#endif // CHOICES_H
