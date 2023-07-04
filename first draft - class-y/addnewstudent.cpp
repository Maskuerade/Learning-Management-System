#include "addnewstudent.h"
#include "ui_addnewstudent.h"
#include "studentsclass.h"
#include <QVector>
#include <QMessageBox>

addNewStudent::addNewStudent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewStudent)
{
    ui->setupUi(this);
}
addNewStudent::~addNewStudent()
{
    delete ui;
}
// add new student
bool f20=false, f1=false,f2=false,f3=false,f4=false,f5=false,repeated_ids=false,repeated_mails=false,repeated_mobs=false;
void addNewStudent::on_donestd_btn_clicked()
{  //repeated_ids=false,repeated_mails=false,repeated_mobs=false;
    if (f1&&f2&&f3&&f4&&f5&&f20)
    {studentsClass * s = new studentsClass();
    s->first_name = ui->stud_fname_txt->text();
    s->middle_name=ui->stud_mname_txt->text();
    s->last_name = ui->stud_lname_txt->text();
    s->mail = ui->stud_mail->text();
    s->mob= ui->stud_mob->text();
    s->id = ui->stud_id->text();
    //to calc the age from q date edit -_-
    int current_year = QDate::currentDate().year();
    s->age = current_year - (ui->dob_dateedit->date().year());

    for (auto ss : oldAllStds){
        if(ss->id==s->id&&ss->mail==s->mail&&ss->mob==s->mob) {repeated_ids=true,repeated_mails=true,repeated_mobs=true;break;}
        else if(ss->id==s->id&&ss->mail!=s->mail&&ss->mob!=s->mob){repeated_ids=true,repeated_mails=false,repeated_mobs=false;break;}
        else if (ss->mail==s->mail&&ss->id!=s->id&&ss->mob!=s->mob){repeated_ids=false,repeated_mails=true,repeated_mobs=false;break;}
        else if (ss->mob==s->mob&&ss->id!=s->id&&ss->mail!=s->mail){repeated_ids=false,repeated_mails=false,repeated_mobs=true;break;}
    }

    if(!repeated_ids&&!repeated_mails&&!repeated_mobs){
    QVector<studentsClass*> one_s;
    one_s.push_back(s);
// clearing the data in the lineEdit
    ui->stud_fname_txt->clear();
    ui->stud_mname_txt->clear();
    ui->stud_lname_txt->clear();
    ui->stud_mail->clear();
    ui->stud_mob->clear();
    ui->stud_id->clear();
    emit sendStudData(one_s);
    }
    else if(repeated_ids) {QMessageBox::critical(this, "repeated" ,"id is repeated");repeated_ids=0;}
    else if(repeated_mobs){QMessageBox::critical(this, "repeated" ,"the mobile number is repeated");repeated_mobs=0;}
    else if(repeated_mails){QMessageBox::critical(this, "repeated" ,"the mail is repeated");repeated_mails=0;}
    //need to predect which two to return them back to false
    else if(repeated_mails&&repeated_mobs&&repeated_ids){QMessageBox::critical(this, "repeated" ,"mail,mob number and id are repeated");repeated_ids=repeated_mails=repeated_mobs=0;}
    else QMessageBox::critical(this, "repeated" ,"two of the data is repeated");
    }
    else
    {QMessageBox::critical(this, "wrong" ,"invalid data");}
}
// set vallidation to "add new functionallity"

void addNewStudent::on_stud_fname_txt_textChanged(const QString &fname)
{
    bool flag=false;
           for (int i =0;i<fname.size();i++)
           {
               if (fname[i].isLetter())
                   flag=true;
               else if (!fname[i].isLetter())
               {
                   flag=false;
                   break;
               }
            }
         if(fname.size()<3||fname.size()>15||fname.contains(' ')||!flag){
                   ui->stud_fname_txt->setStyleSheet("color: red;");
                   f1=false;
                   }
                   else
                   {
                       ui->stud_fname_txt->setStyleSheet("color: black; ");
                       f1=true;
                   }

}
void addNewStudent::on_stud_mname_txt_textChanged(const QString &mname)
{
    bool flag=false;
           for (int i =0;i<mname.size();i++)
           {
               if (mname[i].isLetter())
                   flag=true;
               else if (!mname[i].isLetter())
               {
                   flag=false;
                   break;
               }
            }
         if(mname.size()<3||mname.size()>15||mname.contains(' ')||!flag){
                   ui->stud_mname_txt->setStyleSheet("color: red;");
                   f5=false;
                   }
                   else
                   {
                       ui->stud_mname_txt->setStyleSheet("color: black; ");
                       f5=true;
                   }
}
void addNewStudent::on_stud_lname_txt_textChanged(const QString &lname)
{
    bool flag=false;
            for (int i =0;i<lname.size();i++)
            {
                if (lname[i].isLetter())
                    flag=true;
                else if (!lname[i].isLetter())
                {
                    flag=false;
                    break;
                }
            }
         if(lname.size()<3||lname.size()>15||lname.contains(' ')||!flag)

         { ui->stud_lname_txt->setStyleSheet("color: red; ");
         f2=false;}

            else
         { ui->stud_lname_txt->setStyleSheet("color: black; ");
         f2=true;}
}
void addNewStudent::on_stud_mail_textChanged(const QString &mail)
{
    if(mail.size()<=17||mail.contains(' ')||!mail.contains("@eng-st.cu.edu.eg"))

    {
        ui->stud_mail->setStyleSheet("color: red; ");
        f3=false;
    }
                else
    {
        ui->stud_mail->setStyleSheet("color: black; ");
        f3=true;
    }
}
void addNewStudent::on_stud_mob_textChanged(const QString &num)
{
    bool flag;
              for (int i =0;i<num.size();i++)
              {
                  if (num[i].isDigit())
                      flag=true;
                  else if (!num[i].isDigit())
                  {
                      flag=false;
                      break;
                  }
              }
              if(num.size()!=11||!flag)
              {ui->stud_mob->setStyleSheet("color: red; ");
              f4=false;}
              else
              {ui->stud_mob->setStyleSheet("color: black; ");
              f4=true;}
}


void addNewStudent::recieve_all_stds(QVector<studentsClass*> vectr){
    oldAllStds = vectr;
};


void addNewStudent::on_stud_id_textChanged(const QString &arg1)
{
    bool flag;
              for (int i =0;i<arg1.size();i++)
              {
                  if (arg1[i].isDigit())
                      flag=true;
                  else if (!arg1[i].isDigit())
                  {
                      flag=false;
                      break;
                  }
              }
              if(arg1.size()!=5||!flag)
              {ui->stud_id->setStyleSheet("color: red; ");
              f20=false;}
              else
              {ui->stud_id->setStyleSheet("color: black; ");
              f20=true;}
}

