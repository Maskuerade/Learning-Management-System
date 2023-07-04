#include "add_course_to_prof.h"
#include "ui_add_course_to_prof.h"

#include <QMessageBox>
#include <QListWidgetItem>

QTableWidget * tblP;
QListWidget * listP;

add_course_to_prof::add_course_to_prof(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_course_to_prof)
{
    ui->setupUi(this);
}

add_course_to_prof::~add_course_to_prof()
{
    delete ui;
}
void add_course_to_prof::recieveAllClassesP(QVector<course*> all){
    recievedClassesP = all;
}
void add_course_to_prof::ProrecievefNameAndTitle(QString name,QString tit){
    prof_name=name;
    prof_title=tit;
    ui->prof_name_lbl->setText(prof_name);
    ui->prof_title_lbl->setText(prof_title);
}
void add_course_to_prof::load_data_p(){
    QTableWidget * tblP = ui->courses_to_choose_tbl_p;
    tblP->setRowCount(recievedClassesP.size());
    //the real set data
        for(int i = 0; i<recievedClassesP.size();++i){
            QTableWidgetItem * course_name = new QTableWidgetItem(recievedClassesP[i]->name);
            QTableWidgetItem * course_code = new QTableWidgetItem(recievedClassesP[i]->code);
            //set data in the table
            tblP->setItem(i,0,course_name);
            tblP->setItem(i,1,course_code);
        }
}

void add_course_to_prof::on_courses_to_choose_tbl_p_cellDoubleClicked(int row, int column)
{
    QTableWidget * tblP = ui->courses_to_choose_tbl_p;
    QListWidget * list = ui->chosed_classes_list_p;
    QString chosen_course_name = tblP->item(row,0)->text();
    int already_found = 0;
    for(int i=2;i<list->count();i++){
        if(chosen_course_name==list->item(i)->text()){already_found=1;break;}
    }
if(already_found)QMessageBox::information(this,"invalid choice","this course is already found in the list");
else{
    QListWidgetItem * list_itemP = new QListWidgetItem(chosen_course_name);
    list->addItem(list_itemP);
    list_elementsP.push_back(chosen_course_name);
}
}


void add_course_to_prof::on_chosed_classes_list_p_itemDoubleClicked(QListWidgetItem *item)
{
    QListWidget * listP = ui->chosed_classes_list_p;
    list_elementsP.removeOne(item->text());
    int row = listP->row(item);
    if (row>1) delete listP->takeItem(row);
}


void add_course_to_prof::on_done_adding_prof_to_class_clicked()
{
    emit sendListElementsP(list_elementsP);
    QListWidget * listP = ui->chosed_classes_list_p;
    listP->clear();
    listP->addItem("chosen classes");
    listP->addItem("---------------------");
    list_elementsP.clear();
}

