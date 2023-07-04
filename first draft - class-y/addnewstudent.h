#ifndef ADDNEWSTUDENT_H
#define ADDNEWSTUDENT_H

#include <QDialog>
#include "studentsclass.h"

namespace Ui {
class addNewStudent;
}
/*!
 * \brief The addNewStudent class
 * this class is inherited from QDialog class
 * a special type of classes in qt
 * it shows a dialogue to add the new student data
 */
class addNewStudent : public QDialog
{
    Q_OBJECT

public:
    explicit addNewStudent(QWidget *parent = nullptr);
    ~addNewStudent();
    /*!
     * \brief oldAllStds
     * this vector recieves all old students to compare the data of the old students
     */
    QVector<studentsClass*> oldAllStds;

public slots:
    /*!
     * \brief recieve_all_stds
     * this function stores the data of existing students to store them in old All Stds
     * \param vectr
     */
    void recieve_all_stds(QVector<studentsClass*> vectr);

signals:
    /*!
       * \brief sendStudData
       * this function sends the data of the newly created student to the main window to store it in our data structure
       * \param vector
       */
      void sendStudData(QVector<studentsClass*> vector);

private slots:
      /*!
       * \brief on_donestd_btn_clicked
       * when clicking done, it checks the data of the newly created student and emits the signal to send it to the main window if it's valid
       */
      void on_donestd_btn_clicked();
      /*!
       * \brief on_stud_fname_txt_textChanged
       * just a data validation function
       * \param arg1
       */
      void on_stud_fname_txt_textChanged(const QString &arg1);
      /*!
       * \brief on_stud_mname_txt_textChanged
       * just a data validation function
       * \param arg1
       */
      void on_stud_mname_txt_textChanged(const QString &arg1);
      /*!
       * \brief on_stud_lname_txt_textChanged
       * just a data validation function
       * \param arg1
       */
      void on_stud_lname_txt_textChanged(const QString &arg1);
      /*!
       * \brief on_stud_mail_textChanged
       * just a data validation function on the run
       * \param arg1
       */
      void on_stud_mail_textChanged(const QString &arg1);
      /*!
       * \brief on_stud_mob_textChanged
       * just a data validation function on the run
       * \param arg1
       */
      void on_stud_mob_textChanged(const QString &arg1);
      /*!
       * \brief on_stud_id_textChanged
       * just a data validation function on the run
       * \param arg1
       */
      void on_stud_id_textChanged(const QString &arg1);

private:
    Ui::addNewStudent *ui;
};

#endif // ADDNEWSTUDENT_H
