#ifndef ADDSTUDENTTOCLASS_H
#define ADDSTUDENTTOCLASS_H

#include <QDialog>
#include <QListWidgetItem>

#include "course.h"

namespace Ui {
class addStudentToClass;
}
/*!
 * \brief The addStudentToClass class
 * this is a special type of classes in qt whick creates a dialogue when openning the object created
 * the dialogue assigns the student to a previously found classes
 */
class addStudentToClass : public QDialog
{
    Q_OBJECT

public:
    explicit addStudentToClass(QWidget *parent = nullptr);
    ~addStudentToClass();
public slots:
    /*!
     * \brief recieveStdName
     * this function recieves the student's name to be written up the dialogue
     * \param name
     */
    void recieveStdName(QString name);
    /*!
     * \brief recieveAllClasses
     * this function stores the data of the existing classes in the data base in recieved classes vector
     * \param all
     */
    void recieveAllClasses(QVector<course*> all);
    /*!
     * \brief load_data
     * this function loads the data of all classes in a table to let the user choose as they want from all of them
     */
    void load_data();
signals:
    /*!
     * \brief sendListElements
     * this functin sends list elements to main window to store its values in the vector carrying the names of target classes for the chosen student
     * \param elements
     */
    void sendListElements(QVector<QString> elements);

private slots:
    /*!
     * \brief on_courses_to_choose_tbl_cellDoubleClicked
     * this function
     * \param row
     * \param column
     */
    void on_courses_to_choose_tbl_cellDoubleClicked(int row, int column);
    /*!
     * \brief on_done_adding_std_to_class_clicked
     *
     */

    void on_done_adding_std_to_class_clicked();

    void on_chosed_classes_list_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::addStudentToClass *ui;
    //recieve std name
    QString std_name;
    //recieve all classes
    QVector <course*> recievedClasses;
    //store list data
    QVector <QString> list_elements;
};

#endif // ADDSTUDENTTOCLASS_H
