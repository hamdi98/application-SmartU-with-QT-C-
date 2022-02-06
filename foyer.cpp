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
#include "foyer.h"




bool Foyer::payer(QString id , QString motp )
{
   QSqlQuery query  ;

   query.prepare("update carte set solde = solde - 1700  where id_carte = '"+id+"'and motc ='"+ motp+"'  ");
   query.bindValue(":id_carte",id);
   query.bindValue(":motc",motp);
   return query.exec();

 }

bool Foyer ::demande(int cine ,QString nom,QString email ,int tel  )
{
 QSqlQuery q ;

 QString res  = QString  :: number(cine) ;
QString res1  = QString  :: number(tel) ;

  q.prepare("insert into DEMANDEF (CIND, NOMD,EMAILD,TELD) values (:cine,:nom ,:email, :tel)");

q.bindValue(":cine",res);
q.bindValue(":nom",nom);
q.bindValue(":email",email);
q.bindValue(":tel",res1);
return q.exec();




}


Foyer::Foyer()
{
cine = 0 ;
nom =" "  ;
email =" ";
id_chambre = " ";

}

Foyer::Foyer(int cine , QString nom ,QString email ,QString id_chambre )
{
this->cine = cine ;
this->nom = nom ;
this ->email = email ;
this ->id_chambre = id_chambre ;
}

bool Foyer ::ajouter()
{
 QSqlQuery q ;

 QString res  = QString  :: number(cine) ;
q.prepare("insert into foyer(cine,nom,email, id_chambre)values(:cine,:nom,:email ,:id_chambre)");

q.bindValue(":cine",res);
q.bindValue(":nom",nom);
q.bindValue(":email",email);
q.bindValue(":id_chambre",id_chambre);
return q.exec();
}



bool Foyer :: modifier(int id ,  QString nom ,  QString email ,  QString id_chambre)
{
    QString res = QString :: number (id) ;
    QSqlQuery q;
     q.prepare("UPDATE FOYER set NOM='"+nom+"' , email= '"+email+"',id_chambre= '"+id_chambre+"' where cine='"+res+"'");
    q.bindValue(":nom",nom);
    q.bindValue(":email",email);
    q.bindValue(":id_chambre",id_chambre);
    q.bindValue(":id",res);

    return q.exec();

}


bool Foyer :: supp (int id)
{

    QSqlQuery query ;
  QString res = QString :: number  (id) ;
    query.prepare("delete from DEMANDEF where CIND = :id") ;
    query.bindValue(":id",res);
    return query.exec();
}
bool Foyer :: supp2 (int id)
{

    QSqlQuery query ;
  QString res = QString :: number  (id) ;
    query.prepare("delete from foyer where CINE = :id") ;
    query.bindValue(":id",res);
    return query.exec();
}





QSqlQueryModel *  Foyer :: afficher_foyer()
 {
     QSqlQuery *q = new QSqlQuery();
     QSqlQueryModel *model = new QSqlQueryModel();
     q->prepare("SELECT *FROM foyer");
     q->exec();
     model->setQuery(*q);

  return model ;


}
QSqlQueryModel *  Foyer :: afficher_demande()
 {

     QSqlQueryModel *model = new QSqlQueryModel();
     model->setQuery("SELECT *FROM demandef");

  return model ;


}



