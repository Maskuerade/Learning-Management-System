#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QVector>

//classes headers
#include "course.h"
#include "adminCLASS.h"
#include "profsclass.h"
#include "studentsclass.h"

//dialogues
#include "addnewprof.h"
#include "addnewstudent.h"
#include "addnewcourse.h"
#include "addstudenttoclass.h"
#include "set_class_grade_dialogue.h"
#include "add_course_to_prof.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
/*!
 * \brief The MainWindow class
 * this is the main window of all UIs and carry most of the important functions to run the program
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /*!
     * \brief alldata structures
     *   data structues to store all what we have createdd in our program like a (database) access
     *   these vectors carry pointer to objects
     */
    QVector <course*> allClasses;
    QVector<admin> allAdmins;
    QVector<profsCLASS*> allProfs;
    QVector<studentsClass*> allStudents;
    /*!
     * \brief listElement
     *  list of classes added to the chosen student
     */
    QVector<QString> listElement;
    /*!
     * \brief listElementP
     * lise of all classes added to a chosen prof
     */
    QVector<QString> listElementP;
    /*!
     * \brief stddd_index
     * the index of the student that was double clicked
     */
    int stddd_index;
    int class_index;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_prf_btn_3_clicked();

    void on_std_btn_3_clicked();

    void on_ad_student_clicked();

    void on_pushButton_3_clicked();

    void on_back_courses_to_lists_clicked();

    void on_class_btn_3_clicked();
    /*!
     * \brief on_add_new_coourse_btn_clicked
     * this button opens the window to add new course
     */
    void on_add_new_coourse_btn_clicked();

    void on_back_from_profs_to_lists_clicked();
    /*!
     * \brief on_searchStd_btn_clicked
     * this button searches for a student using the id
     */
    void on_searchStd_btn_clicked();
    /*!
     * \brief on_students_tblw_cellDoubleClicked
     * this function is evoked when double clicking on a table cell to show that student profile
     * \param row
     * \param column
     */
    void on_students_tblw_cellDoubleClicked(int row, int column);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();
    /*!
     * \brief on_add_std_to_course_clicked
     * this button opens a window to add new student
     */
    void on_add_std_to_course_clicked();
    /*!
     * \brief on_delete_course_btn_clicked
     * this button deletes a course from the data structure
     */
    void on_delete_course_btn_clicked();
    /*!
     * \brief on_remove_prof_clicked
     * this button removes a prof from the data base
     */
    void on_remove_prof_clicked();
    /*!
     * \brief on_set_std_grade_clicked
     * this button opens a window to set the grades for the chosen student
     */
    void on_set_std_grade_clicked();
    /*!
     * \brief on_search_a_prof_clicked
     * this button enables the user to search for a prof using the id
     */
    void on_search_a_prof_clicked();
    /*!
     * \brief on_prof_tblw_cellDoubleClicked
     * this function returns the row and column of the cell
     * the row reperesnts the index of the prof in our data structure
     * \param row
     * \param column
     */
    void on_prof_tblw_cellDoubleClicked(int row, int column);

    void on_pushButton_19_clicked();

    void on_add_std_to_course_5_clicked();
    /*!
     * \brief on_courses_tblw_cellDoubleClicked
     * this button opens the profile of the chosen class
     * \param row
     * \param column
     */
    void on_courses_tblw_cellDoubleClicked(int row, int column);

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

public slots:

    void onVectorReceived(QVector<admin> one_ad);

    /*!
     * \brief recieveProfData,setdata_in_profs_table
     * these two functions recieves the data of the created prof, stores it in our database and sets his basic information in a table
     * \param one_prof
     */
    void recieveProfData(QVector<profsCLASS*> one_prof);
     void setdata_in_profs_table();

     /*!
      * \brief recieveStudData,setdata_in_studs_table
      * these two functions recieves the data of the created student, stores it in our database and sets his basic information in a table
      * \param one_stud
      */
     void recieveStudData(QVector<studentsClass*> one_stud);
     void setdata_in_studs_table();
     /*!
      * \brief recieveCourseData,setdata_in_classes_table
      * these two function recieves the data of the newly created course, stores it in our database and sets his basic information in a table
      * \param vector
      */
     void recieveCourseData(QVector<course*> vector);
     void setdata_in_classes_table();
     /*!
      * \brief recieveListElements
      * this function recives list elements carrying the chosen courses to be added to a specefic student
      * \param listElements
      */
     void recieveListElements(QVector<QString> listElements);
     /*!
      * \brief setCoursesToStudent
      * set chosen course in student data, the tables and set the student in the course
      */
     void setCoursesToStudent();
     /*!
      * \brief recieve_new_myClasses,update_my_classes_table
      * these functions recieve the classes that their grades have been added to them in the students vector and use these vectors to update the tables
      * \param ind
      * \param newC
      */
     void recieve_new_myClasses(int ind,QVector<QPair<QString,QString>> newC);
     void update_my_classes_table(int indxxx);
     /*!
      * \brief recieveListElementsP,setCoursesToProf
      * these functions recieve list elements carrying the courses chosen to be assigned to the specefic professor
      * \param listElementsProf
      */
     void recieveListElementsP(QVector<QString> listElementsProf);
     void setCoursesToProf();

signals:
     /*!
     * \brief sendCoursesData
     * when this signal is emmited it sends all courses to add new student to the add new course window
     * \param all
     */
    void sendCoursesData(QVector<course*> all);
    /*!
     * \brief sendStudentName,sendStudentIndex
     * these two signals when emmited send the chosen student name and index to assigna courses to them
     */
    void sendStudentName(QString);
    void sendStudentIndex(int indx);
    /*!
     * \brief sendAllClasses
     * when this signal is emmited, the window to add courses to that class recieves the data of all classes
     * \param all
     */
    void sendAllClasses(QVector<course*> all);
    /*!
     * \brief sendMyClasses
     * when emmited it sends all classes to the grades window
     * \param all
     */
    void sendMyClasses(QVector<QPair<QString,QString>> all);
    /*!
     * \brief please_set_data,please_set_dataP
     * when emmited set the data in courses table in add course to student/prof window
     */
    void please_set_data();
    void please_set_dataP();
    /*!
     * \brief please_set_my_classes
     * when emmited set the data in courses table in set grade window
     * \param my
     */
    void please_set_my_classes(QVector<QPair<QString,QString>> my);
    /*!
     * \brief sendAllProfs,sendAllStds
     * when emmited send aleardy found data of students/profs tp add new prof/student
     * \param allProfs
     */
    void sendAllProfs(QVector<profsCLASS*> allProfs);
    void sendAllStds(QVector<studentsClass*> allStds);
     void sendPNameAndTitle(QString name,QString tit);

private:
     //main window
    Ui::MainWindow *ui;
    //dialogues
    //add new prof dialogue
    addNewProf * porfW = new addNewProf(this);
    //add new stud dialogue
    addNewStudent * studW = new addNewStudent(this);
    //add new course dialogue
    addNewCourse * courseW = new addNewCourse(this);
    //add classes to student dialogue
    addStudentToClass * addStdToClass = new addStudentToClass(this);
    //assign student grades dialogue
    set_class_grade_dialogue * gradesW = new set_class_grade_dialogue(this);
    //add class to professor dialogue
    add_course_to_prof * addCToP = new add_course_to_prof(this);
};
#endif // MAINWINDOW_H
