#include "addnewcourse.h"
#include "ui_addnewcourse.h"

#include <QVector>
#include <QMessageBox>
//#include <QMutex>

#include "course.h"

//QMutex mutex;

addNewCourse::addNewCourse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewCourse)
{
    ui->setupUi(this);
}

addNewCourse::~addNewCourse()
{
    delete ui;
}
void addNewCourse::recieveAllClasses(QVector <course*> all){
    allRecieved = all;
};


void addNewCourse::on_done_adding_new_course_clicked()
{
    //check valid data before creating the object
    int day_repeated =0 ,hall_repeated = 0,time_repeated = 0, name_repeated =0, code_repeated =0;
    for(int i = 0;i<allRecieved.size();i++){
        if (allRecieved[i]->day == ui->choose_day->currentText()) {day_repeated = 1; break;}
    }
    for(int i = 0;i<allRecieved.size();i++){
        if (allRecieved[i]->period == ui->choose_time->currentText()) {time_repeated = 1; break;}
    }
    for(int i = 0;i<allRecieved.size();i++){
        if (allRecieved[i]->hall == ui->choose_hall->currentText()) {hall_repeated = 1; break;}
    }
    for(int i = 0;i<allRecieved.size();i++){
        if (allRecieved[i]->name == ui->enter_course_name->text()) {name_repeated = 1; break;}
    }
    for(int i = 0;i<allRecieved.size();i++){
        if (allRecieved[i]->code == ui->enter_course_code->text()) {code_repeated = 1; break;}
    }
    //check all
    if(hall_repeated&&time_repeated&&day_repeated) {
        QMessageBox::information(this, "unvalid choices", "This combination of day,time and hall is preserved, please choose another option");
    }else if(name_repeated||code_repeated)QMessageBox::information(this, "course repeated","this course is already found");

    else if(!code_repeated&&!name_repeated) {
        //create pointer to course object
        course * c = new course();
        //set the attributes
        c->name = ui->enter_course_name->text();
        c->code = ui->enter_course_code->text();
        c->day=ui->choose_day->currentText();
        c->hall=ui->choose_hall->currentText();
        c->period=ui->choose_time->currentText();

        //push in the vector and send to mainwindow
        QVector <course*> one_c;
        one_c.push_back(c);
        emit send_course_data(one_c);

        ui->enter_course_code->clear();
        ui->enter_course_name->clear();
        ui->choose_day->setCurrentIndex(0);
        ui->choose_hall->setCurrentIndex(0);
        ui->choose_time->setCurrentIndex(0);
    }

}

