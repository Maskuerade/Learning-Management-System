#ifndef ADDNEWPROF_H
#define ADDNEWPROF_H

#include <QDialog>
#include "profsclass.h"
namespace Ui {
class addNewProf;
}
/*!
 * \brief The addNewProf class
 * this is a special type of classes in qt, class form
 * when creating an object from it and opening it a dialogue appears to the user
 * this dialogue is ued to add new prof to the database
 */
class addNewProf : public QDialog
{
    Q_OBJECT

public:
    explicit addNewProf(QWidget *parent = nullptr);
    ~addNewProf();

private slots:
    /*!
     * \brief on_done_adding_new_prof_clicked
     * when clicking the button, it checks the data of the new prof and sends them to the mainwindow
     */
    void on_done_adding_new_prof_clicked();
    /*!
     * \brief on_prof_fname_txt_textChanged
     * these functions are used to validate the data of the new prof on the run
     * \param arg1
     */
    void on_prof_fname_txt_textChanged(const QString &arg1);
    /*!
     * \brief on_prof_mname_txt_textChanged
     * data validatin function
     * \param arg1
     */
    void on_prof_mname_txt_textChanged(const QString &arg1);
    /*!
     * \brief on_prof_lname_txt_textChanged
     * data validation function
     * \param arg1
     */

    void on_prof_lname_txt_textChanged(const QString &arg1);
    /*!
     * \brief on_prof_mail_textChanged
     * data validation function
     * \param arg1
     */

    void on_prof_mail_textChanged(const QString &arg1);
    /*!
     * \brief on_prof_mob_textChanged
     * data validation function
     * \param arg1
     */

    void on_prof_mob_textChanged(const QString &arg1);
    /*!
     * \brief on_prof_ID_line_edit_textChanged
     * data validation function
     * \param arg1
     */

    void on_prof_ID_line_edit_textChanged(const QString &arg1);

public slots:
    /*!
     * \brief recieve_all_profs
     * this slot is evoked when sending all prof
     * \param vector_1
     */
    void recieve_all_profs(QVector<profsCLASS*> vector_1);

signals:
    /*!
       * \brief sendProfData
       * this signal sends the newly created prof data
       * \param vector
       */
      void sendProfData(QVector<profsCLASS*> vector);

private:
    Ui::addNewProf *ui;
    QVector<profsCLASS*> oldAll;
};

#endif // ADDNEWPROF_H
