#ifndef ADD_COURSE_TO_PROF_H
#define ADD_COURSE_TO_PROF_H

#include "profsClass.h"

#include <QDialog>
#include <QListWidgetItem>

#include "course.h"

namespace Ui {
class add_course_to_prof;
}
/*!
 * \brief The add_course_to_prof class
 * this is a class form that is a part of Qt
 * it allows the user to open a new dialogue when emmiting some signal
 * this dialogue:add_course_to_prof
 * it allows the user to add chosen course to previously chosen professor
 */
class add_course_to_prof : public QDialog
{
    Q_OBJECT

public:
    explicit add_course_to_prof(QWidget *parent = nullptr);
    ~add_course_to_prof();
public slots:
    /*!
     * \brief ProrecievefNameAndTitle,
     *  this a function (slot) to recieve the chosen prof name and title
     * \param name
     * the name of the student
     * \param tit
     * this is the title of the chosen professor
     */
    void ProrecievefNameAndTitle(QString name,QString tit);
    /*!
     * \brief recieveAllClassesP
     * this is a function to recieve all classes
     * \param all
     */
    void recieveAllClassesP(QVector<course*> all);
    /*!
     * \brief load_data_p
     */
    void load_data_p();

private slots:
    /*!
     * \brief on_courses_to_choose_tbl_p_cellDoubleClicked
     * \param row
     * this parameter stores the number of the row to get the name of the course depending on it
     * \param column
     */
    void on_courses_to_choose_tbl_p_cellDoubleClicked(int row, int column);
    /*!
     * \brief on_chosed_classes_list_p_itemDoubleClicked
     * this function triggers removing the double clicked item
     * \param item
     */
    void on_chosed_classes_list_p_itemDoubleClicked(QListWidgetItem *item);
    /*!
     * \brief on_done_adding_prof_to_class_clicked
     * this function sends the elments of the list to main window to store them in the vector specefied to the prof
     */
    void on_done_adding_prof_to_class_clicked();

signals:
    /*!
     * \brief sendListElementsP
     * when this signal is emmited, it sends the list elements to main window
     * \param Pelements
     */
    void sendListElementsP(QVector<QString> Pelements);
private:
    Ui::add_course_to_prof *ui;
    /*!
     * \brief prof_name
     * to recieve prof name and title
     */
    QString prof_name,
    prof_title;
    /*!
     * \brief recievedClassesP
     * recieve all classes
     */
    QVector <course*> recievedClassesP;

    /*!
     * \brief list_elementsP
     * store list data
     */
    QVector <QString> list_elementsP;

};

#endif // ADD_COURSE_TO_PROF_H
