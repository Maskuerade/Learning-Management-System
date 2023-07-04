#ifndef SET_CLASS_GRADE_DIALOGUE_H
#define SET_CLASS_GRADE_DIALOGUE_H

#include <QDialog>
/*!
 *this is a special class in qt to set the grades of assigned courses to student
 */
namespace Ui {
class set_class_grade_dialogue;
}

class set_class_grade_dialogue : public QDialog
{
    Q_OBJECT

public:
    explicit set_class_grade_dialogue(QWidget *parent = nullptr);
    ~set_class_grade_dialogue();
public slots:
    void recieveStdName(QString);
    void recieveMyClasses(QVector<QPair<QString,QString>> all);
    void set_classes(QVector<QPair<QString,QString>> my);
    void recieve_std_index(int indx);
private slots:
    void on_done_setting_grades_btn_clicked();
signals:
    void send_new_my_classes_and_grades(int ind,QVector<QPair<QString,QString>> new_all);
    void send_std_index(int std_index);
private:
    Ui::set_class_grade_dialogue *ui;
    QString std_name;
    QVector<QPair<QString,QString>> allRecieved;
    int studentt_index;
};

#endif // SET_CLASS_GRADE_DIALOGUE_H
