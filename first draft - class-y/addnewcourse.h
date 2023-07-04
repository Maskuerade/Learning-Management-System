#ifndef ADDNEWCOURSE_H
#define ADDNEWCOURSE_H

#include <QDialog>
#include <QVector>

#include "course.h"

namespace Ui {
class addNewCourse;
}
/*!
 * \brief The addNewCourse class
 * this is a special type of classes in qt that open a dialogue when sending the order open
 */
class addNewCourse : public QDialog
{
    Q_OBJECT

public:
    explicit addNewCourse(QWidget *parent = nullptr);
    ~addNewCourse();
    /*!
     * \brief allRecieved
     * this vector stores all the already found courses in the data base so that we don't add an exisitin vector nor repeating day, hall and time
     */
    QVector <course*> allRecieved;



public slots:
    /*!
     * \brief on_done_adding_new_course_clicked
     * this slot is evoked when the user clicks the button
     * it sends the data of the new course to main window to show it and insert students to it in the future...etc
     */
    void on_done_adding_new_course_clicked();

public slots:
    /*!
     * \brief recieveAllClasses
     * this function stores the recieved classes in allRecieved, a vector stores all the already found courses in the data base so that we don't add an exisitin vector nor repeating day, hall and time
     * \param all
     */
    void recieveAllClasses(QVector <course*> all);

signals:
    /*!
     * \brief send_course_data
     * send the data of the new course to be added to all courses in the mainwindow
     * \param vector
     */
    void send_course_data(QVector <course*> vector);

private:
    Ui::addNewCourse *ui;

};

#endif // ADDNEWCOURSE_H
