#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "choices.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
//    void on_pushButton_clicked();

//    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

//    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    choices *choose;
};
#endif // MAINWINDOW_H
