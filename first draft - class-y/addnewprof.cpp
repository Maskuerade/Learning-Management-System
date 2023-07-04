#include "addnewprof.h"
#include "ui_addnewprof.h"
#include "profsclass.h"
#include <QVector>
#include <QDate>
#include <QMessageBox>
addNewProf::addNewProf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewProf)
{
    ui->setupUi(this);
}

addNewProf::~addNewProf()
{
    delete ui;
}
void addNewProf::recieve_all_profs(QVector<profsCLASS*> vector_1){
   oldAll = vector_1;
};
bool f30=false, f6=false,f7=false,f8=false,f9=false,f10=false,unique_id=true,unique_mail=true,unique_mob=true;// khaleha false lama tzabty el slots w el mawdo3 da
void addNewProf::on_done_adding_new_prof_clicked()
{
    if (f6&&f7&&f8&&f9&&f10&&f30){
    profsCLASS * p1 = new profsCLASS();
    p1->first_name = ui->prof_fname_txt->text();
    p1->last_name = ui->prof_lname_txt->text();
    p1->id = ui->prof_ID_line_edit->text();
    p1->middle_name = ui->prof_mname_txt->text();
    p1->mail = ui->prof_mail->text();
    p1->mob = ui->prof_mob->text();
    p1->title = ui->title_dropbox->currentText();
    //to calc the age from q date edit -_-
    int current_year = QDate::currentDate().year();
    p1->age = current_year - (ui->dobprof_dateedit->date().year());
    //check for all
    for(int i = 0;i<oldAll.size();i++){
        if (oldAll[i]->id == p1->id) {unique_id = 0; break;}
    }
    for(int i = 0;i<oldAll.size();i++){
        if (oldAll[i]->mail== p1->mail) {unique_mail = 0; break;}
    }
    for(int i = 0;i<oldAll.size();i++){
        if (oldAll[i]->mob == p1->mob) {unique_mob = 0; break;}
    }

    if(unique_id&&unique_mail&&unique_mob){
    QVector<profsCLASS*> p;
    p.push_back(p1);
    //clearing the texts
    ui->prof_fname_txt->clear();
    ui->prof_lname_txt->clear();
    ui->prof_mname_txt->clear();
    ui->prof_mail->clear();
    ui->prof_mob->clear();
    ui->prof_ID_line_edit->clear();
    emit sendProfData(p);
    }
    else if(!unique_id&&unique_mail&&unique_mob) {QMessageBox::critical(this, "repeated" ,"id is repeated"); unique_id=true;}
    else if(unique_id&&unique_mail&&!unique_mob)QMessageBox::critical(this, "repeated" ,"the mobile number is repeated");
    else if(unique_id&&!unique_mail&&unique_mob)QMessageBox::critical(this, "repeated" ,"the mail is repeated");
    else if(!unique_mail&&!unique_mob&&!unique_id)QMessageBox::critical(this, "repeated" ,"mail,mob number and id are repeated");
    else if(unique_mail&&unique_mob&&unique_id) QMessageBox::critical(this, "repeated" ,"one of the mail,mob number or id is repeated");
    else QMessageBox::critical(this, "repeated" ,"two of the mail,mob number or id is repeated");
    }
    else
    {QMessageBox::critical(this, "wrong" ,"invalid data");}
}


void addNewProf::on_prof_fname_txt_textChanged(const QString &fname)
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
                   ui->prof_fname_txt->setStyleSheet("color: red;");
                   f6=false;
                   }
                   else
                   {
                       ui->prof_fname_txt->setStyleSheet("color: black; ");
                       f6=true;
                   }
}

void addNewProf::on_prof_mname_txt_textChanged(const QString &mname)
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
                   ui->prof_mname_txt->setStyleSheet("color: red;");
                   f7=false;
                   }
                   else
                   {
                       ui->prof_mname_txt->setStyleSheet("color: black; ");
                       f7=true;
                   }
}
void addNewProf::on_prof_lname_txt_textChanged(const QString &lname)
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

         { ui->prof_lname_txt->setStyleSheet("color: red; ");
         f8=false;}

            else
         { ui->prof_lname_txt->setStyleSheet("color: black; ");
         f8=true;}
}


void addNewProf::on_prof_mail_textChanged(const QString &mail)
{
    if(mail.size()<=17||mail.contains(' ')||!mail.contains("@eng-st.cu.edu.eg"))

    {
        ui->prof_mail->setStyleSheet("color: red; ");
        f9=false;
    }
                else
    {
        ui->prof_mail->setStyleSheet("color: black; ");
        f9=true;
    }
}


void addNewProf::on_prof_mob_textChanged(const QString &num)
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
              {ui->prof_mob->setStyleSheet("color: red; ");
              f10=false;}
              else
              {ui->prof_mob->setStyleSheet("color: black; ");
              f10=true;}
}

void addNewProf::on_prof_ID_line_edit_textChanged(const QString &arg1)
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
                  {ui->prof_ID_line_edit->setStyleSheet("color: red; ");
                  f30=false;}
                  else
                  {ui->prof_ID_line_edit->setStyleSheet("color: black; ");
                  f30=true;}
}


