#ifndef STUDENTSCLASS_H
#define STUDENTSCLASS_H

#include <QString>
#include <qmap>
#include <QPair>
/*!
 * \brief The studentsClass class
 * this is a class to generate students objects to store
 */
class studentsClass
{
public:
    studentsClass();

    QString first_name,last_name,middle_name,mob,mail,id;
    int age;

    QVector<QPair<QString,QString>> my_classesNames_and_grades;

};

#endif // STUDENTSCLASS_H
