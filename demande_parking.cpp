#include "demande_parking.h"
#include<QSqlQuery>
#include <QDebug>



demande_parking::demande_parking()
{
    nom="";
    prenom="";
    CIN="";
    EMAIL="";
    date="";
}
demande_parking::demande_parking(QString nom,QString prenom,QString CIN,QString EMAIL,QString date)
{
    this->nom=nom;
    this->prenom=prenom;
    this->CIN=CIN;
    this->EMAIL=EMAIL;
    this->date=date;
}
bool demande_parking::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO DEMANDEP (NOM, PRENOM,CIN,DATED,EMAIL) "
                        "VALUES (:nom,:prenom,:CIN,:EMAIL,:date)");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":CIN", CIN);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":date", date);



    return    query.exec();
}
bool demande_parking::supprimer(QString  ID)
{
QSqlQuery query;

query.prepare("Delete from DEMANDEP where NOM = :id ");
query.bindValue(":id", ID);
return    query.exec();
}




QSqlQueryModel * demande_parking::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select  * from DEMANDEP ");

        return model;
}
