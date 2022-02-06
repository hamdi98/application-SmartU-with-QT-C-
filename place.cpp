#include "place.h"
#include <QDebug>
#include<QSqlQuery>
place::place()
{num="";
ID="";}




place::place(QString num,QString ID)
{
this->num=num;
    this->ID=ID;
}





bool place::ajouter()
{

    QSqlQuery query;
//QString res= QString::number(ID);

    query.prepare("INSERT INTO PLACEP ( NUM,IDPARKING) "
                        "VALUES (:num, :ID)");
query.bindValue(":num", num);
query.bindValue(":ID", ID);



return    query.exec();
}
bool place::supprimer(QString  ID)
{
QSqlQuery query;

query.prepare("Delete from PLACEP where IDPARKING = :id ");
query.bindValue(":id", ID);
return    query.exec();
}




QSqlQueryModel * place::afficher()
{//QSqlQueryModel * model= new QSqlQueryModel();
//model->setQuery("select  NOM,PRENOM from PARKING ");
//model->setHeaderData(0, Qt::Horizontal, QObject::tr("num "));
//model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID"));
 //   return model;
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select  * from PLACEP ");

        return model;
}


bool place ::modifier(QString num,QString id)
{
    /*QSqlQuery q;
    q.prepare("update PARKING set NOM='"+nom2+"',PRENOM='"+prenom2+"',IDPARKING='"+id2+"', where ID=:id2" );

    q.bindValue(":NOM",nom2);
    q.bindValue(":PRENOM",prenom2);
    q.bindValue(":IDPARKING",id2);
    return q.exec();*/
    QSqlQuery q;
    q.prepare("update PLACEP set NUM=:num1 where IDPARKING=:id1" );


    q.bindValue(":num1",num);

    return q.exec();
}

