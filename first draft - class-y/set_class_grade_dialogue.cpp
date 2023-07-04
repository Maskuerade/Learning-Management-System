#include "set_class_grade_dialogue.h"
#include "ui_set_class_grade_dialogue.h"

set_class_grade_dialogue::set_class_grade_dialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::set_class_grade_dialogue)
{
    ui->setupUi(this);
    ui->course_1_grade_ln->setReadOnly(1);
    ui->course_2_grade_ln->setReadOnly(1);
    ui->course_3_grade_ln->setReadOnly(1);
    ui->course_4_grade_ln->setReadOnly(1);
    ui->course_5_grade_ln->setReadOnly(1);
    ui->course_6_grade_ln->setReadOnly(1);
    ui->course_7_grade_ln->setReadOnly(1);
}

set_class_grade_dialogue::~set_class_grade_dialogue()
{
    delete ui;
}

void set_class_grade_dialogue::recieveStdName(QString a){
    std_name = a;
    ui->std_name_lbl->setText(std_name);
};

void set_class_grade_dialogue::recieveMyClasses(QVector<QPair<QString,QString>> all){
    allRecieved = all;
};
void set_class_grade_dialogue::recieve_std_index(int indx){
    studentt_index = indx;
};

void set_class_grade_dialogue::set_classes(QVector<QPair<QString,QString>> my){
    switch(my.size())
    {
    case 1:
          ui->c1_lbl->setText(my[0].first);
          ui->course_1_grade_ln->setReadOnly(0);
        break;

    case 2:
        ui->c1_lbl->setText(my[0].first);
        ui->course_1_grade_ln->setReadOnly(0);
        ui->c2_lbl->setText(my[1].first);
        ui->course_2_grade_ln->setReadOnly(0);
        break;

    case 3:
        ui->c1_lbl->setText(my[0].first);
        ui->course_1_grade_ln->setReadOnly(0);
        ui->c2_lbl->setText(my[1].first);
        ui->course_2_grade_ln->setReadOnly(0);
        ui->c3_lbl->setText(my[2].first);
        ui->course_3_grade_ln->setReadOnly(0);
        break;

    case 4:
        ui->c1_lbl->setText(my[0].first);
        ui->course_1_grade_ln->setReadOnly(0);
        ui->c2_lbl->setText(my[1].first);
        ui->course_2_grade_ln->setReadOnly(0);
        ui->c3_lbl->setText(my[2].first);
        ui->course_3_grade_ln->setReadOnly(0);
        ui->c4_lbl->setText(my[3].first);
        ui->course_4_grade_ln->setReadOnly(0);
        break;

    case 5:
        ui->c1_lbl->setText(my[0].first);
        ui->course_1_grade_ln->setReadOnly(0);
        ui->c2_lbl->setText(my[1].first);
        ui->course_2_grade_ln->setReadOnly(0);
        ui->c3_lbl->setText(my[2].first);
        ui->course_3_grade_ln->setReadOnly(0);
        ui->c4_lbl->setText(my[3].first);
        ui->course_4_grade_ln->setReadOnly(0);
        ui->c5_lbl->setText(my[4].first);
        ui->course_5_grade_ln->setReadOnly(0);
        break;
    case 6:
    {ui->c1_lbl->setText(my[0].first);
        ui->course_1_grade_ln->setReadOnly(0);
        ui->c2_lbl->setText(my[1].first);
        ui->course_2_grade_ln->setReadOnly(0);
        ui->c3_lbl->setText(my[2].first);
        ui->course_3_grade_ln->setReadOnly(0);
        ui->c4_lbl->setText(my[3].first);
        ui->course_4_grade_ln->setReadOnly(0);
        ui->c5_lbl->setText(my[4].first);
        ui->course_5_grade_ln->setReadOnly(0);
        ui->c6_lbl->setText(my[5].first);
        ui->course_6_grade_ln->setReadOnly(0);
        break;}
    case 7:
        ui->c1_lbl->setText(my[0].first);
        ui->course_1_grade_ln->setReadOnly(0);
        ui->c2_lbl->setText(my[1].first);
        ui->course_2_grade_ln->setReadOnly(0);
        ui->c3_lbl->setText(my[2].first);
        ui->course_3_grade_ln->setReadOnly(0);
        ui->c4_lbl->setText(my[3].first);
        ui->course_4_grade_ln->setReadOnly(0);
        ui->c5_lbl->setText(my[4].first);
        ui->course_5_grade_ln->setReadOnly(0);
        ui->c6_lbl->setText(my[5].first);
        ui->course_6_grade_ln->setReadOnly(0);
        ui->c7_lbl->setText(my[6].first);
        ui->course_7_grade_ln->setReadOnly(0);
        break;

    }
}


void set_class_grade_dialogue::on_done_setting_grades_btn_clicked()
{
    switch (allRecieved.size()) {
    case 1:
        allRecieved[0].second=ui->course_1_grade_ln->text();
        break;
    case 2:
        allRecieved[0].second=ui->course_1_grade_ln->text();
        allRecieved[1].second=ui->course_2_grade_ln->text();
         break;
    case 3:
        allRecieved[0].second=ui->course_1_grade_ln->text();
        allRecieved[1].second=ui->course_2_grade_ln->text();
        allRecieved[2].second=ui->course_3_grade_ln->text();
         break;
    case 4:
        allRecieved[0].second=ui->course_1_grade_ln->text();
        allRecieved[1].second=ui->course_2_grade_ln->text();
        allRecieved[2].second=ui->course_3_grade_ln->text();
        allRecieved[3].second=ui->course_4_grade_ln->text();
         break;
    case 5:
        allRecieved[0].second=ui->course_1_grade_ln->text();
        allRecieved[1].second=ui->course_2_grade_ln->text();
        allRecieved[2].second=ui->course_3_grade_ln->text();
        allRecieved[3].second=ui->course_4_grade_ln->text();
        allRecieved[4].second=ui->course_5_grade_ln->text();
         break;
    case 6:
        allRecieved[0].second=ui->course_1_grade_ln->text();
        allRecieved[1].second=ui->course_2_grade_ln->text();
        allRecieved[2].second=ui->course_3_grade_ln->text();
        allRecieved[3].second=ui->course_4_grade_ln->text();
        allRecieved[4].second=ui->course_5_grade_ln->text();
        allRecieved[5].second=ui->course_6_grade_ln->text();
         break;
    case 7:
        allRecieved[0].second=ui->course_1_grade_ln->text();
        allRecieved[1].second=ui->course_2_grade_ln->text();
        allRecieved[2].second=ui->course_3_grade_ln->text();
        allRecieved[3].second=ui->course_4_grade_ln->text();
        allRecieved[4].second=ui->course_5_grade_ln->text();
        allRecieved[5].second=ui->course_6_grade_ln->text();
        allRecieved[6].second=ui->course_7_grade_ln->text();
         break;
    default:
        break;
    }
    emit send_new_my_classes_and_grades(studentt_index,allRecieved);
    //emit send_std_index(studentt_index);
    ui->course_1_grade_ln->clear();
    ui->course_2_grade_ln->clear();
    ui->course_3_grade_ln->clear();
    ui->course_4_grade_ln->clear();
    ui->course_5_grade_ln->clear();
    ui->course_6_grade_ln->clear();
    ui->course_7_grade_ln->clear();

}

