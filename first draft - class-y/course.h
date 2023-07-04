#ifndef COURSE_H
#define COURSE_H
#include <qmap>
#include <QVector>
#include <qstring>
#include <QPair>

using namespace std;
/*!
 * \brief The course class
 * this is a class to create objects representing the courses in the system
 */
class course
{
public:
    course();
    /*!
      * \brief name,code,hall,period,day,...etc
      * they are the attributes of every course
      */
     QString name,code;

     QString hall = "choose lecture hall";
     QString period ="choose lecture time" ;
     QString day ="choose lecture day";

     QVector<QPair<QString,QString>> studentsNames_and_grades;
     QVector<QPair<QString,QString>> profsNames_and_titles;
};

#endif // COURSE_H
