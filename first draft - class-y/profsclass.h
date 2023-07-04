#ifndef PROFSCLASS_H
#define PROFSCLASS_H

#include <QString>
#include <QMap>
/*!
 * \brief The profsCLASS class
 * this is a class to generate objects of professors
 */
class profsCLASS
{
public:
    profsCLASS();

    QString first_name,last_name,middle_name,mob,mail,title,id;
    int age;
    QVector<QString> classesNames;

};

#endif // PROFSCLASS_H
