#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "databaase.h"
//#include "course.h"

#include <QDebug>
#include <QVector>
#include <QMessageBox>
#include <QtAlgorithms>
#include <QFile>



QTableWidget* prof_tbl;
QTableWidget* std_tbl;
QTableWidget * courses_tbl;




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //the first widget to appear
    ui->stacked1->setCurrentWidget(ui->lists);

    //connection to: 1) send prof data so that the new doesn't have the same mail of id, 2)get profs data from dialogue
    connect (porfW,&addNewProf::sendProfData,this,&MainWindow::recieveProfData);
    connect(this,&MainWindow::sendAllProfs,porfW,&addNewProf::recieve_all_profs);
    connect (porfW,&addNewProf::finished,this,&MainWindow::setdata_in_profs_table);

//connection to: 1) send std data so that the new doesn't have the same mail of id, 2)get std data from dialogue    connect (studW,&addNewStudent::sendStudData,this,&MainWindow::recieveStudData);
    connect (studW,&addNewStudent::sendStudData,this,&MainWindow::recieveStudData);
    connect(this,&MainWindow::sendAllStds,studW,&addNewStudent::recieve_all_stds);
    connect (studW,&addNewStudent::finished,this,&MainWindow::setdata_in_studs_table);

    //connection to: 1) send course data for comparison of new D_H_T with old ones
    //2)get courses data from add new course dialogue
    connect(this,&MainWindow::sendCoursesData,courseW,&addNewCourse::recieveAllClasses);
    connect(courseW, &addNewCourse::send_course_data,this,&MainWindow::recieveCourseData);
    connect (courseW,&addNewCourse::finished,this,&MainWindow::setdata_in_classes_table);


    //connection to send std name, allclasses data,and recieve list elements and set data in student classes table
    connect(this,&MainWindow::please_set_data,addStdToClass,&addStudentToClass::load_data);
    connect(this,&MainWindow::sendStudentName,addStdToClass,&addStudentToClass::recieveStdName);
    connect(this,&MainWindow::sendAllClasses,addStdToClass,&addStudentToClass::recieveAllClasses);
    connect(addStdToClass,&addStudentToClass::sendListElements,this,&MainWindow::recieveListElements);
    connect(addStdToClass,&addStudentToClass::finished,this,&MainWindow::setCoursesToStudent);

    //connections to set student grades
    connect(this,&MainWindow::sendStudentName,gradesW,&set_class_grade_dialogue::recieveStdName);
    connect(this,&MainWindow::sendMyClasses,gradesW,&set_class_grade_dialogue::recieveMyClasses);
    connect(this,&MainWindow::please_set_my_classes,gradesW,&set_class_grade_dialogue::set_classes);
    connect(gradesW,&set_class_grade_dialogue::send_new_my_classes_and_grades,this,&MainWindow::recieve_new_myClasses);
    connect(this,&MainWindow::sendStudentIndex,gradesW,&set_class_grade_dialogue::recieve_std_index);
    //connect(gradesW,&set_class_grade_dialogue::send_std_index,this,&MainWindow::update_my_classes_table);
    connect(gradesW,&set_class_grade_dialogue::finished,this,&MainWindow::update_my_classes_table);

    //connect add course to prof dialogue to mainwindow
    connect(this,&MainWindow::please_set_dataP,addCToP,&add_course_to_prof::load_data_p);
    connect(this,&MainWindow::sendPNameAndTitle,addCToP,&add_course_to_prof::ProrecievefNameAndTitle);
    connect(this,&MainWindow::sendAllClasses,addCToP,&add_course_to_prof::recieveAllClassesP);
    connect(addCToP,&add_course_to_prof::sendListElementsP,this,&MainWindow::recieveListElementsP);
    connect(addCToP,&add_course_to_prof::finished,this,&MainWindow::setCoursesToProf);


    prof_tbl = ui->profs_NCT->findChild<QTableWidget*>("prof_tblw");
    prof_tbl->setColumnWidth(0,100);
    prof_tbl->setColumnWidth(1,100);
    prof_tbl->setColumnWidth(2,100);

    std_tbl = ui->students_NIM->findChild<QTableWidget*>("students_tblw");
    std_tbl->setColumnWidth(0,100);
    std_tbl->setColumnWidth(1,100);
    std_tbl->setColumnWidth(2,100);

    courses_tbl = ui->stacked1->findChild<QTableWidget*>("courses_tblw");
    courses_tbl->setColumnWidth(0,200);
    courses_tbl->setColumnWidth(1,100);
    courses_tbl->setColumnWidth(2,100);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(ui->adminUser_LineEdit->text() == "MMNCAF" && ui->AdminPass_LineEdit->text() == "gogo"){
        ui->stacked1->setCurrentWidget(ui->lists);
    }
    else
        QMessageBox::information(this, "INTRUDER" ,"invalid username or password");


}

void MainWindow::onVectorReceived(QVector<admin> one_ad){
    allAdmins.push_back(one_ad[0]);
}

void MainWindow::recieveProfData(QVector<profsCLASS*> one_prof){
    allProfs.push_back(one_prof[0]);
    emit sendAllProfs(allProfs);
}

void MainWindow::recieveStudData(QVector<studentsClass*> one_stud){
    allStudents.push_back(one_stud[0]);
   emit sendAllStds(allStudents);
}

void MainWindow::recieveCourseData(QVector<course*> vector){
    allClasses.push_back(vector[0]);
    emit sendCoursesData(allClasses);
};


void MainWindow::setdata_in_profs_table(){

    prof_tbl->setRowCount(allProfs.size());

    //the real set data
        for(int i = 0; i<allProfs.size();++i){
            QString name_prof = allProfs[i]->first_name +" "+allProfs[i]->middle_name +" "+ allProfs[i]->last_name;
            QTableWidgetItem * prof_name = new QTableWidgetItem(name_prof);
            QTableWidgetItem * prof_id = new QTableWidgetItem(allProfs[i]->id);
            QTableWidgetItem * prof_title = new QTableWidgetItem(allProfs[i]->title);
            switch(allProfs[i]->classesNames.size()){
            case 0: break;
            case 1: {QTableWidgetItem * prof_c1 = new QTableWidgetItem(allProfs[i]->classesNames[0]); prof_tbl->setItem(i,3,prof_c1);break;}
            case 2: {QTableWidgetItem * prof_c1 = new QTableWidgetItem(allProfs[i]->classesNames[0]); prof_tbl->setItem(i,3,prof_c1);
                QTableWidgetItem * prof_c2 = new QTableWidgetItem(allProfs[i]->classesNames[1]); prof_tbl->setItem(i,4,prof_c2);
                break;}
            case 3: {QTableWidgetItem * prof_c1 = new QTableWidgetItem(allProfs[i]->classesNames[0]); prof_tbl->setItem(i,3,prof_c1);
                QTableWidgetItem * prof_c2 = new QTableWidgetItem(allProfs[i]->classesNames[1]); prof_tbl->setItem(i,4,prof_c2);
                QTableWidgetItem * prof_c3 = new QTableWidgetItem(allProfs[i]->classesNames[2]); prof_tbl->setItem(i,5,prof_c3);
                break;}
            }
            //set data in the table
            prof_tbl->setItem(i,0,prof_name);
            prof_tbl->setItem(i,1,prof_id);
            prof_tbl->setItem(i,2,prof_title);

        }
        emit sendAllClasses(allClasses);
        emit please_set_dataP();
}

void MainWindow::setdata_in_studs_table(){

    std_tbl->setRowCount(allStudents.size());

    //the real set data
        for(int i = 0; i<allStudents.size();++i){
            QString name_sd = allStudents[i]->first_name +" "+allStudents[i]->middle_name +" "+ allStudents[i]->last_name;
            QTableWidgetItem * stud_name = new QTableWidgetItem(name_sd);
            QTableWidgetItem * stud_id = new QTableWidgetItem(allStudents[i]->id);
            QTableWidgetItem * ac_year = new QTableWidgetItem("2025");
            //set data in the table
            std_tbl->setItem(i,0,stud_name);
            std_tbl->setItem(i,1,stud_id);
            std_tbl->setItem(i,2,ac_year);
        }

}

void MainWindow::setdata_in_classes_table(){
    courses_tbl->setRowCount(allClasses.size());
    //the real set data
        for(int i = 0; i<allClasses.size();++i){
            QTableWidgetItem * course_name = new QTableWidgetItem(allClasses[i]->name);
            QTableWidgetItem * course_code = new QTableWidgetItem(allClasses[i]->code);
            //set data in the table
            courses_tbl->setItem(i,0,course_name);
            courses_tbl->setItem(i,1,course_code);
        }
        emit sendAllClasses(allClasses);
        emit please_set_data();

}

void MainWindow::on_pushButton_2_clicked()
{
    porfW->open();
}


void MainWindow::on_prf_btn_3_clicked()
{
    //the real set data
        for(int i = 0; i<allProfs.size();++i){
            QString name_prof = allProfs[i]->first_name +" "+allProfs[i]->middle_name +" "+ allProfs[i]->last_name;
            QTableWidgetItem * prof_name = new QTableWidgetItem(name_prof);
            QTableWidgetItem * prof_id = new QTableWidgetItem(allProfs[i]->id);
            QTableWidgetItem * prof_title = new QTableWidgetItem(allProfs[i]->title);
            switch(allProfs[i]->classesNames.size()){
            case 0: break;
            case 1: {QTableWidgetItem * prof_c1 = new QTableWidgetItem(allProfs[i]->classesNames[0]); prof_tbl->setItem(i,3,prof_c1);break;}
            case 2: {QTableWidgetItem * prof_c1 = new QTableWidgetItem(allProfs[i]->classesNames[0]); prof_tbl->setItem(i,3,prof_c1);
                QTableWidgetItem * prof_c2 = new QTableWidgetItem(allProfs[i]->classesNames[1]); prof_tbl->setItem(i,4,prof_c2);
                break;}
            case 3: {QTableWidgetItem * prof_c1 = new QTableWidgetItem(allProfs[i]->classesNames[0]); prof_tbl->setItem(i,3,prof_c1);
                QTableWidgetItem * prof_c2 = new QTableWidgetItem(allProfs[i]->classesNames[1]); prof_tbl->setItem(i,4,prof_c2);
                QTableWidgetItem * prof_c3 = new QTableWidgetItem(allProfs[i]->classesNames[2]); prof_tbl->setItem(i,5,prof_c3);
                break;}
            }
            //set data in the table
            prof_tbl->setItem(i,0,prof_name);
            prof_tbl->setItem(i,1,prof_id);
            prof_tbl->setItem(i,2,prof_title);

        }
    ui->stacked1->setCurrentWidget(ui->profs_NCT);
    emit sendAllProfs(allProfs);
}




void MainWindow::on_std_btn_3_clicked()
{
    std_tbl->setRowCount(allStudents.size());

    //the real set data
        for(int i = 0; i<allStudents.size();++i){
            QString name_sd = allStudents[i]->first_name +" "+allStudents[i]->middle_name +" "+ allStudents[i]->last_name;
            QTableWidgetItem * stud_name = new QTableWidgetItem(name_sd);
            QTableWidgetItem * stud_id = new QTableWidgetItem(allStudents[i]->id);
            QTableWidgetItem * ac_year = new QTableWidgetItem("2025");
            //set data in the table
            std_tbl->setItem(i,0,stud_name);
            std_tbl->setItem(i,1,stud_id);
            std_tbl->setItem(i,2,ac_year);
        }
    emit sendAllStds(allStudents);
    ui->stacked1->setCurrentWidget(ui->students_NIM);
}


void MainWindow::on_ad_student_clicked()
{
    studW->open();
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->stacked1->setCurrentWidget(ui->lists);
}


void MainWindow::on_back_courses_to_lists_clicked()
{
    courses_tbl->clear();
    courses_tbl->setHorizontalHeaderLabels({"course name","course code"});
    ui->stacked1->setCurrentWidget(ui->lists);
}


void MainWindow::on_class_btn_3_clicked()
{
    courses_tbl->setRowCount(allClasses.size());
    //the real set data
        for(int i = 0; i<allClasses.size();++i){
            QTableWidgetItem * course_name = new QTableWidgetItem(allClasses[i]->name);
            QTableWidgetItem * course_code = new QTableWidgetItem(allClasses[i]->code);
            //set data in the table
            courses_tbl->setItem(i,0,course_name);
            courses_tbl->setItem(i,1,course_code);
        }
    ui->stacked1->setCurrentWidget(ui->courses_NC);
}


void MainWindow::on_add_new_coourse_btn_clicked()
{
    emit sendCoursesData(allClasses);
    courseW->open();
}


void MainWindow::on_back_from_profs_to_lists_clicked()
{
    prof_tbl->clear();
    prof_tbl->setHorizontalHeaderLabels({"professor name","professor ID","title"});
    ui->stacked1->setCurrentWidget(ui->lists);
}

void MainWindow::on_searchStd_btn_clicked()
{
    bool doesStdExist;
    int temp;
    QString Std_id = ui->searchStd_LineEdit->text();
    for(int i=0; i<allStudents.size(); i++){
        if(Std_id == allStudents[i]->id)
        {doesStdExist = true;
            temp = i;
            break;}
        else
        {doesStdExist = false;}
    }
    if(doesStdExist){

              QLabel* std_name_lbl = ui->StudentProfile->findChild<QLabel*>("stdName_TxtLable");
              QString fullname= allStudents[temp]->first_name +" "+ allStudents[temp]->middle_name +" "+ allStudents[temp]->last_name;
              std_name_lbl->setText(fullname);

              QLabel* std_ID_lbl = ui->StudentProfile->findChild<QLabel*>("StdId_textLable");
              QString Id= allStudents[temp]->id;
              std_ID_lbl->setText(Id);

              QLabel* std_mobile_lbl = ui->StudentProfile->findChild<QLabel*>("StdMobile_textLable");
              QString mobile= allStudents[temp]->mob;
              std_mobile_lbl->setText(mobile);

              QLabel* std_email_lbl = ui->StudentProfile->findChild<QLabel*>("Stdemail_textLable");
              QString email= allStudents[temp]->mail;
              std_email_lbl->setText(email);

              QLabel* std_age_lbl = ui->StudentProfile->findChild<QLabel*>("StdDob_TextLable");
              int i = allStudents[temp]->age;
              QString age = QString::number(i);
              std_age_lbl->setText(age);

              QLabel* std_year_lbl = ui->StudentProfile->findChild<QLabel*>("ACyear_textLable");
              QString year= "2025";
              std_year_lbl->setText(year);

              ui->stacked1->setCurrentWidget(ui->StudentProfile);
    }
    else
        QMessageBox::information(this, "Title" ,"this student doesn't exist");
}



void MainWindow::on_students_tblw_cellDoubleClicked(int row, int column)
{

    int temp = row;
          QLabel* std_name_lbl = ui->StudentProfile->findChild<QLabel*>("stdName_TxtLable");
          QString fullname= allStudents[temp]->first_name +" "+ allStudents[temp]->middle_name +" "+ allStudents[temp]->last_name;
          std_name_lbl->setText(fullname);

          QLabel* std_ID_lbl = ui->StudentProfile->findChild<QLabel*>("StdId_textLable");
          QString Id= allStudents[temp]->id;
          std_ID_lbl->setText(Id);

          QLabel* std_mobile_lbl = ui->StudentProfile->findChild<QLabel*>("StdMobile_textLable");
          QString mobile= allStudents[temp]->mob;
          std_mobile_lbl->setText(mobile);

          QLabel* std_email_lbl = ui->StudentProfile->findChild<QLabel*>("Stdemail_textLable");
          QString email= allStudents[temp]->mail;
          std_email_lbl->setText(email);

          QLabel* std_age_lbl = ui->StudentProfile->findChild<QLabel*>("StdDob_TextLable");
          int i = allStudents[temp]->age;
          QString age = QString::number(i);
          std_age_lbl->setText(age);

          QLabel* std_year_lbl = ui->StudentProfile->findChild<QLabel*>("ACyear_textLable");
          QString year= "2025";
          std_year_lbl->setText(year);

          stddd_index = row;
          QTableWidget * classes_of_students =  ui->stacked1->findChild<QTableWidget*>("std_courses_tblw");

          classes_of_students->setRowCount(allStudents[row]->my_classesNames_and_grades.size());
          //if there're names and grades for that student allStudents[row]
          for(int k=0;k<allStudents[row]->my_classesNames_and_grades.size();k++){
              QTableWidgetItem * class_of_std_name = new QTableWidgetItem(allStudents[row]->my_classesNames_and_grades[k].first);
              QTableWidgetItem * class_of_std_grade = new QTableWidgetItem(allStudents[row]->my_classesNames_and_grades[k].second);
              classes_of_students->setItem(k,0,class_of_std_name);
              classes_of_students->setItem(k,1,class_of_std_grade);
          }          ui->stacked1->setCurrentWidget(ui->StudentProfile);
          emit sendStudentName(ui->stacked1->findChild<QLabel*>("stdName_TxtLable")->text());
          emit sendStudentIndex(temp);

}


void MainWindow::on_pushButton_4_clicked()
{
    ui->stacked1->setCurrentWidget(ui->students_NIM);
}


void MainWindow::on_pushButton_5_clicked()
{
    int temp;
        QModelIndexList indexes = ui->students_tblw->selectionModel()->selection().indexes();
          for (int i = 0; i < indexes.count(); ++i)
          {
              QModelIndex index = indexes.at(i);
               temp=index.row();
          }
        ui->students_tblw->removeRow(ui->students_tblw->currentRow());
        allStudents.removeAt(temp);

}
void MainWindow::on_delete_course_btn_clicked()
{
    int temp;
            QModelIndexList indexes = ui->courses_tblw->selectionModel()->selection().indexes();
              for (int i = 0; i < indexes.count(); ++i)
              {
                  QModelIndex index = indexes.at(i);
                   temp=index.row();
              }
            ui->courses_tblw->removeRow(ui->courses_tblw->currentRow());
            allClasses.removeAt(temp);
}


void MainWindow::on_remove_prof_clicked()
{
    int temp;
            QModelIndexList indexes = ui->prof_tblw->selectionModel()->selection().indexes();
              for (int i = 0; i < indexes.count(); ++i)
              {
                  QModelIndex index = indexes.at(i);
                   temp=index.row();
              }
            ui->prof_tblw->removeRow(ui->prof_tblw->currentRow());
            allProfs.removeAt(temp);
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->stacked1->setCurrentWidget(ui->courses_NC);
}


void MainWindow::on_add_std_to_course_clicked()
{
    addStdToClass->open();
    //emit sendAllClasses(allClasses);
}

void MainWindow::recieveListElements(QVector<QString> listElements){
    listElement = listElements;
}

void MainWindow::setCoursesToStudent(){
    QString target_std_id =  ui->stacked1->findChild<QLabel*>("StdId_textLable")->text();
    //get student index in the vector
    //int i = 0;
    //for(i;i<allStudents.size();i++){
     //   if(allStudents[i]->id==target_std_id) break;
    //}
    //push all chosen classes in the classes of the chosen student
    for(int j=0;j<listElement.size();j++){
        allStudents[stddd_index]->my_classesNames_and_grades.push_back({listElement[j],"N/A"});
    }
    //the same size as listElement
    //find target courses in allClasses and add all students to it
    for(int j=0;j<listElement.size();j++){
        QString c_j_name = listElement[j];
        auto it = std::find_if(allClasses.begin(), allClasses.end(), [c_j_name](course * obj) {
                return obj->name == c_j_name;
            });
        // (needs a pointer to class) auto it = std::find_if(allClasses.begin(), allClasses.end(),c_j_name);
        int index_of_j_target_course = it - allClasses.begin();
        QString full_target_std_name = allStudents[stddd_index]->first_name + " "+allStudents[stddd_index]->middle_name+" "+allStudents[stddd_index]->last_name;
        allClasses[index_of_j_target_course]->studentsNames_and_grades.push_back({full_target_std_name,"N/A"});
    }
    //set the data in classes of that student table
    QTableWidget * classes_of_students =  ui->stacked1->findChild<QTableWidget*>("std_courses_tblw");
    classes_of_students->setRowCount(allStudents[stddd_index]->my_classesNames_and_grades.size());
    for(int k=0;k<allStudents[stddd_index]->my_classesNames_and_grades.size();k++){
        QTableWidgetItem * class_of_std_name = new QTableWidgetItem(allStudents[stddd_index]->my_classesNames_and_grades[k].first);
        QTableWidgetItem * class_of_std_grade = new QTableWidgetItem(allStudents[stddd_index]->my_classesNames_and_grades[k].second);
        classes_of_students->setItem(k,0,class_of_std_name);
        classes_of_students->setItem(k,1,class_of_std_grade);
    }
    //what about grades, now that i know my courses as student, make the grade window ready
    emit please_set_my_classes(allStudents[stddd_index]->my_classesNames_and_grades);
    listElement.clear();
}



void MainWindow::on_set_std_grade_clicked()
{
    QString target_std_id =  ui->stacked1->findChild<QLabel*>("StdId_textLable")->text();
    //get student index in the vector
    int i = 0;
    // da rakam kam in all students
    for(i;i<allStudents.size();i++){
        if(allStudents[i]->id==target_std_id) break;
    }
    emit sendMyClasses(allStudents[i]->my_classesNames_and_grades);
    if (allStudents[i]->my_classesNames_and_grades.size()==0)QMessageBox::warning(this,"error","The student isn't assigned to any course yet");
    else gradesW->open();
}

//recieve after change in grade, al mafrood
void MainWindow::MainWindow::recieve_new_myClasses(int ind, QVector<QPair<QString,QString>> vec){
    allStudents[ind]->my_classesNames_and_grades = vec;
    //be3addad el elements in my classes as student
    //find class index in all classes
    //you have student index (name in allClasses)
    //index of class among all classes
    for(int m=0;m<allStudents[ind]->my_classesNames_and_grades.size();m++){
            QString c_j_name = allStudents[ind]->my_classesNames_and_grades[m].first;
            auto it = std::find_if(allClasses.begin(), allClasses.end(), [c_j_name](course * obj) {
                    return obj->name == c_j_name;
                });
            int index_of_j_target_course = it - allClasses.begin();

            QString full_target_std_name = allStudents[stddd_index]->first_name + " "+allStudents[stddd_index]->middle_name+" "+allStudents[stddd_index]->last_name;
            //get the index of already existing student in students names and grades
            int q=0;
            for(int q =0;q<allClasses[index_of_j_target_course]->studentsNames_and_grades.size();q++) {
            if(QString(allClasses[index_of_j_target_course]->studentsNames_and_grades[q].first)== full_target_std_name) //allStudents[ind]->first_name+ " "+allStudents[ind]->middle_name +" "+allStudents[ind]->last_name) break;
            //index of class in my classes
            //int ind_of_clss_in_my_clsses =0;
            //for(ind_of_clss_in_my_clsses; ind_of_clss_in_my_clsses < allStudents[ind]->my_classesNames_and_grades.size();ind_of_clss_in_my_clsses++) if(c_j_name==) break;
            allClasses[index_of_j_target_course]->studentsNames_and_grades[q].second = allStudents[ind]->my_classesNames_and_grades[m].second;
        }
    }
    }

//update after change in grades, emitted when the dialogue is closed

void MainWindow::update_my_classes_table(int){
    //set the data in classes of that student table
    QTableWidget * classes_of_students =  ui->stacked1->findChild<QTableWidget*>("std_courses_tblw");
    classes_of_students->setRowCount(allStudents[stddd_index]->my_classesNames_and_grades.size());
    for(int k=0;k<allStudents[stddd_index]->my_classesNames_and_grades.size();k++){
        QTableWidgetItem * class_of_std_name = new QTableWidgetItem(QString(allStudents[stddd_index]->my_classesNames_and_grades[k].first));
        QTableWidgetItem * class_of_std_grade = new QTableWidgetItem(QString(allStudents[stddd_index]->my_classesNames_and_grades[k].second));
        classes_of_students->setItem(k,0,class_of_std_name);
        classes_of_students->setItem(k,1,class_of_std_grade);
    }
    listElement.clear();
}

void MainWindow::on_search_a_prof_clicked()
{
    bool doesStaffExist;
       int temp;
       QString prof_id = ui->search_prof_LineEdit->text();
       for(int i=0; i<allProfs.size(); i++) {
           if(prof_id == allProfs[i]->id)
           {doesStaffExist = true;
               temp = i;
               break;}
           else
           {doesStaffExist = false;}
   }    if(doesStaffExist) {
           QLabel* prof_name_lbl = ui->prof_profile->findChild<QLabel*>("prof_name_lbl");
           QString fullname= allProfs[temp]->first_name +" "+ allProfs[temp]->middle_name +" "+ allProfs[temp]->last_name;
           prof_name_lbl->setText(fullname);

           QLabel* prof_ID_lbl = ui->prof_profile->findChild<QLabel*>("prof_id_lbl");
           QString Id= allProfs[temp]->id;
           prof_ID_lbl->setText(Id);

           QLabel *prof_mobile_lbl = ui->prof_profile->findChild<QLabel*>("prof_mob_lbl");
           QString mobile= allProfs[temp]->mob;
           prof_mobile_lbl->setText(mobile);

           QLabel *prof_email_lbl = ui->prof_profile->findChild<QLabel*>("prof_mail_lbl");
           QString email= allProfs[temp]->mail;
           prof_email_lbl->setText(email);

           QLabel* prof_age_lbl = ui->prof_profile->findChild<QLabel*>("prof_age_lbl");
           int i = allProfs[temp]->age;
           QString age = QString::number(i);
           prof_age_lbl->setText(age);

           QLabel *prof_title_lbl = ui->prof_profile->findChild<QLabel*>("ACyear_textLable__2");
           QString title = allProfs[temp]->title;
          prof_title_lbl->setText(title);

           ui->stacked1->setCurrentWidget(ui->prof_profile);
   }
   else
     QMessageBox::information(this, "wrong" ,"this prof doesn't exist");
       ui->stacked1->findChild<QLineEdit*>("search_prof_LineEdit")->clear();
}


void MainWindow::on_prof_tblw_cellDoubleClicked(int row, int column)
{
    int temp = row;
       QLabel* prof_name_lbl = ui->prof_profile->findChild<QLabel*>("prof_name_lbl");
       QString fullname= allProfs[temp]->first_name +" "+ allProfs[temp]->middle_name +" "+ allProfs[temp]->last_name;
       prof_name_lbl->setText(fullname);

       QLabel *prof_ID_lbl = ui->prof_profile->findChild<QLabel*>("prof_id_lbl");
       QString Id= allProfs[temp]->id;
       prof_ID_lbl->setText(Id);

       QLabel* prof_mobile_lbl = ui->prof_profile->findChild<QLabel*>("prof_mob_lbl");
       QString mobile= allProfs[temp]->mob;
       prof_mobile_lbl->setText(mobile);

       QLabel *prof_email_lbl = ui->prof_profile->findChild<QLabel*>("prof_mail_lbl");
       QString email= allProfs[temp]->mail;
       prof_email_lbl->setText(email);

       QLabel *prof_age_lbl = ui->prof_profile->findChild<QLabel*>("prof_age_lbl");
       int i = allProfs[temp]->age;
       QString age = QString::number(i);
       prof_age_lbl->setText(age);

       QLabel* prof_title_lbl = ui->prof_profile->findChild<QLabel*>("ACyear_textLable__2");
       QString title = allProfs[temp]->title;
      prof_title_lbl->setText(title);

      QTableWidget * classes_of_prof =  ui->stacked1->findChild<QTableWidget*>("prof_classes_tblw");
      classes_of_prof->setRowCount(allProfs[row]->classesNames.size());
      switch(allProfs[row]->classesNames.size()){
      case 0: classes_of_prof->setRowCount(0);break;
      default:
          for(int k=0;k<allProfs[i]->classesNames.size();k++){
              QTableWidgetItem * class_of_prof_name = new QTableWidgetItem(allProfs[i]->classesNames[k]);
              QTableWidgetItem * class_of_prof_title = new QTableWidgetItem(allProfs[i]->title);
              classes_of_prof->setItem(k,0,class_of_prof_name);
              classes_of_prof->setItem(k,1,class_of_prof_title);
              QTableWidgetItem * yearr = new QTableWidgetItem("2025");
              classes_of_prof->setItem(k,2,yearr);}
          break;
        }
      ui->stacked1->setCurrentWidget(ui->prof_profile);

  emit sendPNameAndTitle(ui->stacked1->findChild<QLabel*>("prof_name_lbl")->text(),ui->stacked1->findChild<QLabel*>("ACyear_textLable__2")->text());
}


void MainWindow::on_pushButton_19_clicked()
{
    ui->stacked1->setCurrentWidget(ui->profs_NCT);
}

void MainWindow::recieveListElementsP(QVector<QString> listElementsProf){
    listElementP = listElementsProf;
};

void  MainWindow::setCoursesToProf(){
    QString target_prof_id =  ui->stacked1->findChild<QLabel*>("prof_id_lbl")->text();
    //get student index in the vector
    int i = 0;
    for(i;i<allProfs.size();i++){
        if(allProfs[i]->id==target_prof_id) break;
    }
    //push all chosen classes in the classes of the chosen student
    for(int j=0;j<listElementP.size();j++){
        allProfs[i]->classesNames.push_back(listElementP[j]);
    }
    //the same size as listElement
    //find target courses in allClasses and add all target profs to it
    for(int j=0;j<listElementP.size();j++){
        QString c_j_name = listElementP[j];
        auto it = std::find_if(allClasses.begin(), allClasses.end(), [c_j_name](course * obj) {
                return obj->name == c_j_name;
            });
        // (needs a pointer to class) auto it = std::find_if(allClasses.begin(), allClasses.end(),c_j_name);
        int index_of_j_target_course = it - allClasses.begin();
        QString full_target_prf_name = allProfs[i]->first_name + " "+allProfs[i]->middle_name+" "+allProfs[i]->last_name;
        allClasses[index_of_j_target_course]->profsNames_and_titles.push_back({full_target_prf_name,allProfs[i]->title});
    }
    //set the data in classes of that student table
    QTableWidget * classes_of_prof =  ui->stacked1->findChild<QTableWidget*>("prof_classes_tblw");
    classes_of_prof->setRowCount(allProfs[i]->classesNames.size());
    for(int k=0;k<allProfs[i]->classesNames.size();k++){
        QTableWidgetItem * class_of_prof_name = new QTableWidgetItem(allProfs[i]->classesNames[k]);
        QTableWidgetItem * class_of_prof_title = new QTableWidgetItem(allProfs[i]->title);
        classes_of_prof->setItem(k,0,class_of_prof_name);
        classes_of_prof->setItem(k,1,class_of_prof_title);
        QTableWidgetItem * yearr = new QTableWidgetItem("2025");
        classes_of_prof->setItem(k,2,yearr);
    }
    listElementP.clear();
}

void MainWindow::on_add_std_to_course_5_clicked()
{
    addCToP->open();
}


void MainWindow::on_courses_tblw_cellDoubleClicked(int row, int column)
{
    class_index = row;
    ui->stacked1->findChild<QLabel*>("course_name_lbl")->setText(allClasses[row]->name);
    ui->stacked1->findChild<QLabel*>("course_code_lbl")->setText(allClasses[row]->code);
    QString course_schedule = "day " + allClasses[row]->day + " Hall" + allClasses[row]->hall +allClasses[row]->period;
    ui->stacked1->findChild<QLabel*>("course_schedule_lbl")->setText(course_schedule);
    switch(allClasses[row]->profsNames_and_titles.size()){
    case 0:     { ui->stacked1->findChild<QLabel*>("profs_in_class_lbl")->setText("no profs yet");break;}
    case 1:      {  QString profs_in_me = "the " + allClasses[row]->profsNames_and_titles[0].second + " "+allClasses[row]->profsNames_and_titles[0].first;
                   ui->stacked1->findChild<QLabel*>("profs_in_class_lbl")->setText(profs_in_me);break;}
    case 2:{        QString profs_in_me = "the " + allClasses[row]->profsNames_and_titles[0].second + " "+allClasses[row]->profsNames_and_titles[0].first
                + "and the " + allClasses[row]->profsNames_and_titles[1].second + " "+allClasses[row]->profsNames_and_titles[1].first;
                 ui->stacked1->findChild<QLabel*>("profs_in_class_lbl")->setText(profs_in_me);break;}
    case 3:
        QString profs_in_me = "the " + allClasses[row]->profsNames_and_titles[0].second + " "+allClasses[row]->profsNames_and_titles[0].first
            + "and the " + allClasses[row]->profsNames_and_titles[1].second + " "+allClasses[row]->profsNames_and_titles[1].first
            + " and the "+ allClasses[row]->profsNames_and_titles[2].second + " "+allClasses[row]->profsNames_and_titles[2].first;
    ui->stacked1->findChild<QLabel*>("profs_in_class_lbl")->setText(profs_in_me);break;}
    QTableWidget* std_in_me_and_grades = ui->stacked1->findChild<QTableWidget*>("students_in_me_and_grades");

    if(allClasses[row]->studentsNames_and_grades.size()!=0){
            std_in_me_and_grades->setRowCount(allClasses[row]->studentsNames_and_grades.size());
    for(int l=0;l<allClasses[row]->studentsNames_and_grades.size();l++){
        QTableWidgetItem* std = new QTableWidgetItem(allClasses[row]->studentsNames_and_grades[l].first);
        QTableWidgetItem* grade = new QTableWidgetItem(allClasses[row]->studentsNames_and_grades[l].second);
        std_in_me_and_grades->setItem(l,0,std);
        std_in_me_and_grades->setItem(l,1,grade);
    }
    }else std_in_me_and_grades->setRowCount(0);
    ui->stacked1->setCurrentWidget(ui->ClassProfile);
}


void MainWindow::on_pushButton_8_clicked()
{

                    {
                        QFile f("C:/Users/mirna/Desktop/gallllllll/build-untitled1-Desktop_Qt_6_4_0_MinGW_64_bit-Debug/students.csv");
                                    QTextStream s(&f);
                                       f.open(QIODevice::WriteOnly|QIODevice::Truncate);
                                    for(auto i:allProfs){
                                        s<<i->first_name+","+i->last_name+", "+i->id+","<<i->title+","<<"\n";
                                        for(int m=0;m<i->classesNames.size();m++){
                                            s<<i->classesNames[m]<<"\n";
                                        }


                                    }
                }
}



void MainWindow::on_pushButton_7_clicked()
{

    QFile f("C:/Users/mirna/Desktop/gallllllll/build-untitled1-Desktop_Qt_6_4_0_MinGW_64_bit-Debug/students.csv");
                    QTextStream s(&f);
                       f.open(QIODevice::WriteOnly|QIODevice::Truncate);
                    for(auto i:allStudents){
                        s<<i->first_name+","+i->last_name+", "+i->id+","<<"\n";
                        for(int k=0;k<i->my_classesNames_and_grades.size();k++){
                           s<<i->my_classesNames_and_grades[k].first<<","<<i->my_classesNames_and_grades[k].second<<"\n";
                        }
            }
}
