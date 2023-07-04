#include "addstudenttoclass.h"
#include "ui_addstudenttoclass.h"

//#include <QDebug>
#include <QMessageBox>
#include <QListWidgetItem>

QTableWidget * tbl;
QListWidget * list;

addStudentToClass::addStudentToClass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addStudentToClass)
{
    ui->setupUi(this);

}

addStudentToClass::~addStudentToClass()
{
    delete ui;
}

void addStudentToClass::recieveAllClasses(QVector<course*> all){
    recievedClasses = all;
}

void addStudentToClass::recieveStdName(QString name){
    std_name=name;
    ui->std_name->setText(name);
}

void addStudentToClass::load_data()
{
    QTableWidget * tbl = ui->courses_to_choose_tbl;
    tbl->setRowCount(recievedClasses.size());
    //the real set data
        for(int i = 0; i<recievedClasses.size();++i){
            QTableWidgetItem * course_name = new QTableWidgetItem(recievedClasses[i]->name);
            QTableWidgetItem * course_code = new QTableWidgetItem(recievedClasses[i]->code);
            //set data in the table
            tbl->setItem(i,0,course_name);
            tbl->setItem(i,1,course_code);
        }
}


void addStudentToClass::on_courses_to_choose_tbl_cellDoubleClicked(int row, int column)
{
    QTableWidget * tbl = ui->courses_to_choose_tbl;
    QListWidget * list = ui->chosed_classes_list;
    QString chosen_course_name = tbl->item(row,0)->text();
    int already_found = 0;
    for(int i=2;i<list->count();i++){
        if(chosen_course_name==list->item(i)->text()){already_found=1;break;}
    }
if(already_found)QMessageBox::information(this,"invalid choice","this course is already found in the list");
else{
    QListWidgetItem * list_item = new QListWidgetItem(chosen_course_name);
    list->addItem(list_item);
    list_elements.push_back(chosen_course_name);
}

}


void addStudentToClass::on_done_adding_std_to_class_clicked()
{
    emit sendListElements(list_elements);
    QListWidget * list = ui->chosed_classes_list;
    list->clear();
    list->addItem("chosen classes");
    list->addItem("---------------------");
    list_elements.clear();

//    for(int i=2;i<list->count();i++){
//        QListWidgetItem* item = list->takeItem(i);
//        item->setText(NULL);
//    }
        // The item has been removed from the QListWidget, but we still have a pointer to it
        //delete item;}
}


void addStudentToClass::on_chosed_classes_list_itemDoubleClicked(QListWidgetItem *item)
{
    QListWidget * list = ui->chosed_classes_list;
    list_elements.removeOne(item->text());
    int row = list->row(item);
    if (row>1) delete list->takeItem(row);

}

