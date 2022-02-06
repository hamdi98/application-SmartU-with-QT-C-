#include "etudiantt.h"
#include "ui_etudiantt.h"
#include"foyer.h"
#include <QString>
#include <iostream>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtDebug>
#include <QMessageBox>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include"qmessagebox.h"
#include"smtp.h"
#include<QVariant>
#include <QModelIndex>
#include <iostream>
etudiantt::etudiantt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::etudiantt)
{
    ui->setupUi(this);
}

etudiantt::~etudiantt()
{
    delete ui;
}



void etudiantt :: arduino_verif()
{
    QByteArray data=A.read_from_arduino();
    ui->ard->setText(data);
    envoie();
  }
void etudiantt :: envoie()
{
     QString l;
     QSqlQuery q;
    QByteArray d;
   l=ui->ard->text();
   q.prepare("select * from foyer where cine=:l1");
   q.bindValue(":l1",l);
  if (q.exec())
  {
      int count=0;
      while(q.next())
      {
          count++;
      }
      if (count==1)
      {
          d="1";
          A.write_to_arduino(d);
      }
      else
      {
          d="0";
          A.write_to_arduino(d);
      }
  }


}
void etudiantt::on_demande_clicked()
{

    int   cine2 = ui->cin1->text().toInt() ;
    QString  nom2= ui ->nom1->text() ;
   QString email = ui->email1->text() ;
  int   tl = ui->tel1->text().toInt() ;

Foyer  e;
     bool test = e.demande(cine2,nom2, email,tl ) ;
     if (test)
     {



         QMessageBox::information (nullptr, QObject::tr("demande  envoyer avec sucess !"),
                     QObject::tr( "Click Cancel to exit."), QMessageBox::Cancel);
    }
     else
         QMessageBox::critical(nullptr, QObject::tr("demande non sucess !"),
                     QObject::tr( "Click Cancel to exit."), QMessageBox::Cancel);


}



void etudiantt::on_pushButton_2_clicked()
{

    QString id= ui->id->text() ;
       QString  motp = ui ->mdp->text() ;
       Foyer e;
            bool test = e.payer(id , motp ) ;

            if (test)
            {

                QMessageBox::information (nullptr, QObject::tr("paiement avec sucess !"),
                            QObject::tr( "Click Cancel to exit."), QMessageBox::Cancel);
}
            else
                QMessageBox::critical(nullptr, QObject::tr("paiement non sucess !"),
                            QObject::tr( "Click Cancel to exit."), QMessageBox::Cancel);


}

void etudiantt::on_annulerdemande_clicked()
{

int  id= ui->cin2->text().toInt() ;
Foyer e ;
bool test = e.supp(id);
if (test)
{

    QMessageBox::information (nullptr, QObject::tr("annulation  avec sucess !"),
                QObject::tr( "Click Cancel to exit."), QMessageBox::Cancel);
}
else
    QMessageBox::critical(nullptr, QObject::tr("annulation non sucess !"),
                QObject::tr( "Click Cancel to exit."), QMessageBox::Cancel);

}
